// Reference: https://qiita.com/tanakh/items/0ba42c7ca36cd29d0ac8
macro_rules! input {
    (source = $s:expr, $($r:tt)*) => {
        // Read from string `s`
        let mut iter = $s.split_whitespace();
        input_inner!{ iter, $($r)* }
    };
    ($($r:tt)*) => {
        // Read from standard input
        let s = {
            use std::io::Read;
            let mut s = String::new();
            std::io::stdin().read_to_string(&mut s).unwrap();
            s
        };
        input!{ source = s, $($r)* }
    };
}

macro_rules! input_inner {
    ($iter:expr) => {};
    ($iter:expr,) => {};
    ($iter:expr, $var:ident : $t:tt $($r:tt)*) => {
        let $var = read_value!($iter, $t);
        input_inner!{ $iter $($r)* }
    };
}

macro_rules! read_value {
    ($iter:expr, ( $($t:tt),* )) => {
        // `edge: (usize, usize)`
        ( $(read_value!($iter, $t)),* )
    };
    ($iter:expr, [ $t:tt; $len:expr ]) => {
        // `mat: [[i32: m]; n]` is expanded into `mat: [i32: m]` and then `mat: i32`
        (0..$len).map(|_| read_value!($iter, $t)).collect::<Vec<_>>()
    };
    ($iter:expr, chars) => {
        $iter.next().unwrap().chars().collect::<Vec<char>>()
    };
    ($iter:expr, bytes) => {
        $iter.next().unwrap().bytes().collect::<Vec<u8>>()
    };
    ($iter:expr, usize1) => {
        // `edges: [(usize1, usize1); m]`
        read_value!($iter, usize) - 1
    };
    ($iter:expr, $t:ty) => {
        $iter.next().unwrap().parse::<$t>().expect("Parse error")
    };
}

fn main() {
    input! {
        n: (usize, u32),
        m: usize,
        s: chars,
        t: bytes,
    }
}
