use std::error::Error;
use std::fs::{File, OpenOptions};
use std::io::{self, Read, Write};
use byteorder::{ReadBytesExt, WriteBytesExt};

struct Node {
    value: i32,
    next: Option<Box<Node>>,
}

impl Node {
    fn new(value: i32) -> Self {
        Self {
            value,
            next: None,
        }
    }
}

struct Stack {
    head: Option<Box<Node>>,
    size: usize,
}

impl Stack {
    fn new() -> Self {
        Self { head: None, size: 0 }
    }

    fn push(&mut self, value: i32) {
        let new_node = Box::new(Node {
            value,
            next: self.head.take(),
        });
        self.head = Some(new_node);
        self.size += 1;
    }

    fn pop(&mut self) -> Option<i32> {
        self.head.take().map(|node| {
            self.size -= 1;
            node.value
        })
    }

    fn peek(&self) -> Option<&i32> {
        self.head.as_ref().map(|node| &node.value)
    }

    fn len(&self) -> usize {
        self.size
    }

    fn iter(&self) -> impl Iterator<Item = i32> + '_ {
        let mut current = self.head.as_ref();
        std::iter::from_fn(move || {
            current.map(|node| {
                current = node.next.as_ref();
                node.value
            })
        })
    }

    fn write_to_file(&self, filename: &str) -> Result<(), Box<dyn Error>> {
        let mut file = OpenOptions::new()
            .create(true)
            .write(true)
            .open(filename)?;

        let size_bytes = self.size.to_ne_bytes();
        file.write_all(&size_bytes)?;
        for node in self.iter() {
            let bytes = node.to_ne_bytes();
            file.write_all(&bytes)?;
        }
        Ok(())
    }

    fn read_from_file(filename: &str) -> Result<Self, Box<dyn Error>> {
        let mut file = OpenOptions::new()
            .read(true)
            .open(filename)?;

        let mut size_bytes = [0; 8]; // Assume 64-bit architecture
        file.read_exact(&mut size_bytes)?;
        let size = usize::from_ne_bytes(size_bytes);

        let mut head: Option<Box<Node>> = None;
        for _ in 0..size {
            let mut bytes = [0; 4];
            file.read_exact(&mut bytes)?;
            let mut value = i32::from_ne_bytes(bytes);
            let new_node = Box::new(Node { value, next: head });
            head = Some(new_node);
        }

        Ok(Self { head, size })
    }
}

fn main() {
    let mut stack = Stack::new();
    stack.push(10);
    stack.push(20);

    stack.write_to_file("stack_data.bin").unwrap();

    let mut new_stack = Stack::read_from_file("stack_data.bin").unwrap();
    println!("Elements after reading from file:");
    for value in new_stack.iter() {
        println!("{}", value);
    }
}
