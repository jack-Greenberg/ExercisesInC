// cards.rs - Card counting for rusty computer creatures
use std::io::{stdin, stdout, Write};

fn prompt_user(card_name: &mut String) {
    print!("Enter the card_name: ");
    stdout().flush().unwrap();
    stdin().read_line(card_name).unwrap();
}

fn update_count(val: i32, count: &mut i32) {
    if (val > 2) && (val < 7) {
        *count += 1;
    } else if val == 10 {
        *count -= 1;
    }
}

fn main() {
    let mut count = 0;

    loop {
        let mut card_name = String::new();
        let mut val = 0;
        prompt_user(&mut card_name);

        match card_name.chars().nth(0).unwrap() {
            'K' | 'Q' | 'J' => { val = 10 },
            'A' => { val = 11 },
            'X' => { break },
            _ => {
                match card_name.trim().parse::<i32>() {
                    Ok(v) => {
                        val = v
                    },
                    Err(_) => println!("{:?} is not an integer", card_name),
                }
            }
        }

        update_count(val, &mut count);
        println!("{}", count);
    }
}
