use std::fmt;

struct MyNode {
    value: i32,
    next: Option<Box<MyNode>>,
}

impl MyNode {
    fn new(val: i32, following: Option<Box<MyNode>>) -> Self {
        MyNode { value: val, next: following }
    }
}

struct MyStack {
    size: usize,
    head: Option<Box<MyNode>>,
}

impl MyStack {
    fn new() -> Self {
        MyStack { head: None, size: 0 }
    }

    fn push(&mut self, val: i32) {
        let new_element = Box::new(MyNode::new(val, self.head.take()));
        self.head = Some(new_element);
        self.size += 1;
    }

    fn pop(&mut self) {
        if self.size == 1 {
            self.head = None;
            self.size -= 1;
        } else {
            if let Some(ref mut head) = self.head {
                self.head = head.next.take();
            }
            self.size -= 1;
        }
    }

    fn get_last(&self) -> i32 {
        self.head.as_ref().unwrap().value
    }
}

impl fmt::Display for MyStack {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        let mut curr = self.head.as_ref();
        while let Some(node) = curr {
            write!(f, "[{}]", node.value)?;
            curr = node.next.as_ref();
            if curr.is_some() {
                write!(f, " -> ")?;
            }
        }
        Ok(())
    }
}



struct TreeNode {
    data: i32,
    left: Option<Box<TreeNode>>,
    right: Option<Box<TreeNode>>,
}

impl TreeNode {
    fn new(data: i32) -> Self {
        TreeNode {
            data,
            left: None,
            right: None,
        }
    }

    fn insert(&mut self, data: i32) -> &mut Self {
        if data < self.data {
            if self.left.is_none() {
                self.left = Some(Box::new(TreeNode::new(data)));
            } else {
                self.left.as_mut().unwrap().insert(data);
            }
        } else if data > self.data {
            if self.right.is_none() {
                self.right = Some(Box::new(TreeNode::new(data)));
            } else {
                self.right.as_mut().unwrap().insert(data);
            }
        }
        self
    }

    fn remove(self: Box<Self>, data: i32) -> Option<Box<TreeNode>> {
        if data < self.data {
            if let Some(left) = self.left {
                let new_left = left.remove(data);
                return Some(Box::new(TreeNode {
                    left: new_left,
                    ..*self
                }));
            }
        } else if data > self.data {
            if let Some(right) = self.right {
                let new_right = right.remove(data);
                return Some(Box::new(TreeNode {
                    right: new_right,
                    ..*self
                }));
            }
        } else {
            if self.left.is_none() && self.right.is_none() {
                return None;
            }
            if self.left.is_none() {
                return self.right;
            }
            if self.right.is_none() {
                return self.left;
            }
            let mut min_node = self.right.as_ref().unwrap();
            while let Some(left) = min_node.left.as_ref() {
                min_node = left;
            }
            let min_value = min_node.data;
            let new_right = self.right.unwrap().remove(min_value);
            return Some(Box::new(TreeNode {
                data: min_value,
                left: self.left,
                right: new_right,
            }));
        }
        Some(self)
    }

    fn print(&self, level: usize) {
        if let Some(ref right) = self.right {
            right.print(level + 1);
        }
        println!("{:indent$}", self.data, indent = level * 4);
        if let Some(ref left) = self.left {
            left.print(level + 1);
        }
    }
}

struct TreeBalanced {
    root: Option<Box<TreeNode>>,
}

impl TreeBalanced {
    fn new() -> Self {
        TreeBalanced { root: None }
    }

    fn insert(&mut self, data: i32) {
        if self.root.is_none() {
            self.root = Some(Box::new(TreeNode::new(data)));
        } else {
            self.root.as_mut().unwrap().insert(data);
        }
    }

    fn del(&mut self, data: i32) {
        if let Some(root) = self.root.take() {
            self.root = root.remove(data);
        }
    }

    fn print_tree(&self) {
        if let Some(ref root) = self.root {
            root.print(0);
        }
    }
}

#[cfg(test)]

mod stack{
    use super::*;
    #[test]
    fn push_test(){
        let mut stack = MyStack::new();
        stack.push(1);
        stack.push(2);
        assert_eq!(stack.size, 2);
        assert_eq!(stack.head.as_ref().unwrap().value, 2);
    }
    #[test]
    fn pop_test(){
        let mut stack = MyStack::new();
        stack.push(1);
        stack.push(2);
        stack.push(3);
        stack.pop();
        assert_eq!(stack.size, 2);
        assert_eq!(stack.head.as_ref().unwrap().value, 2);
        stack.pop();
        stack.pop();
        assert_eq!(stack.size, 0);
    }
    #[test]
    fn get_last_test(){
        let mut stack = MyStack::new();
        stack.push(1);
        stack.push(2);
        stack.push(3);
        assert_eq!(stack.get_last(), 3);
    }
    #[test]
    fn print_stack_test(){
        let mut stack = MyStack::new();
        stack.push(1);
        stack.push(2);
        stack.push(3);
        println!("{}",stack);
    }
}

mod tree{
    use super::*;
    #[test]
    fn tree_insert_test(){
        let mut tree = TreeBalanced::new();
        tree.insert(0);
        tree.insert(5);
        tree.insert(10);
        tree.insert(3);
        tree.insert(-5);
        tree.insert(-10);
        tree.insert(-3);
        assert_eq!(tree.root.as_ref().unwrap().data, 0);
        assert_eq!(tree.root.unwrap().right.unwrap().data, 5);
    }
    #[test]
    fn tree_del_test(){
        let mut tree = TreeBalanced::new();
        tree.insert(0);
        tree.insert(5);
        tree.insert(10);
        tree.insert(3);
        tree.insert(100);
        tree.insert(-5);
        tree.insert(-10);
        tree.insert(-3);
        tree.insert(-100);
        tree.del(-100);
        tree.del(100);
        tree.del(5);
        tree.del(-5);
        tree.insert(0);
        tree.print_tree();
        assert_eq!(tree.root.as_ref().unwrap().data, 0);
        assert_eq!(tree.root.unwrap().right.unwrap().data, 10);
    }
}
