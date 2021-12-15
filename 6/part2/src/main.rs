use std::fs;
use std::env;

fn main() {
    let args: Vec<String> = env::args().collect();
    let file_path = &args[1];
    let contents = fs::read_to_string(file_path).expect("File not found");
    let fishes = contents.split(',');
    let mut res: Vec<u64> = vec![0; 9];

    for i in fishes.into_iter() {
        res[i.parse::<usize>().unwrap()] += 1;
    }
    for _ in 0..256 {
        let mut temp_res: Vec<u64> = vec![0; 9];
        for i in 0..res.len() {
            if i == 0 {
                temp_res[8] = res[0];
                temp_res[6] += res[0];
            } else {
                temp_res[i - 1] += res[i];
            }
        }
        res = temp_res.clone();
    }
    println!("res: {}", res.iter().sum::<u64>())
}
