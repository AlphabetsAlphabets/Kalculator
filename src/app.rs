use eframe::{egui, epi};
use egui::widgets;
use egui::TextStyle;

use super::parsing::Lexer;

pub struct App {
    display: String,
    answer: usize,
}

impl Default for App {
    fn default() -> Self {
        App {
            display: "".to_string(),
            answer: 0,
        }
    }
}

fn button(ui: &mut egui::Ui, text: &str) -> egui::Response {
    let button = egui::Button::new(text);
    let button = ui.add_sized(egui::Vec2 { x: 40.0, y: 40.0 }, button);
    button
}

impl epi::App for App {
    fn name(&self) -> &str {
        "Kal"
    }

    // TODO: Add a vertical spacer to spread the buttons out.
    // Also look at button_padding
    fn update(&mut self, ctx: &egui::CtxRef, frame: &mut epi::Frame<'_>) {
        let Self { display, answer } = self;

        egui::TopPanel::top("Calculations").show(ctx, |ui| {
            ui.add_sized(
                egui::Vec2 { x: 240.0, y: 80.0 },
                widgets::Label::new(&display),
            )
        });

        egui::CentralPanel::default().show(ctx, |ui| {
            ui.horizontal(|ui| {
                if button(ui, "1").clicked() {
                    *display = format!("{}{}", display, "1".to_string());
                }
                if button(ui, "2").clicked() {
                    *display = format!("{}{}", display, "2".to_string());
                }
                if button(ui, "3").clicked() {
                    *display = format!("{}{}", display, "3".to_string());
                }
                if button(ui, "+").clicked() {
                    *display = format!("{}{}", display, "+".to_string());
                }
                if button(ui, "-").clicked() {
                    *display = format!("{}{}", display, "-".to_string());
                }
            });

            ui.horizontal(|ui| {
                if button(ui, "4").clicked() {
                    *display = format!("{}{}", display, "4".to_string());
                }

                if button(ui, "5").clicked() {
                    *display = format!("{}{}", display, "5".to_string());
                }

                if button(ui, "6").clicked() {
                    *display = format!("{}{}", display, "6".to_string());
                }

                if button(ui, "÷").clicked() {
                    *display = format!("{}{}", display, "÷".to_string());
                }

                if button(ui, "×").clicked() {
                    *display = format!("{}{}", display, "×".to_string());
                }
            });

            ui.horizontal(|ui| {
                if button(ui, "7").clicked() {
                    *display = format!("{}{}", display, "7".to_string());
                }

                if button(ui, "8").clicked() {
                    *display = format!("{}{}", display, "8".to_string());
                }

                if button(ui, "9").clicked() {
                    *display = format!("{}{}", display, "9".to_string());
                };

                if button(ui, "%").clicked() {
                    *display = format!("{}{}", display, "%".to_string());
                }

                if button(ui, "AC").clicked() {
                    display.clear();
                }
            });

            ui.horizontal(|ui| {
                button(ui, "");
                if button(ui, "0").clicked() {
                    *display = format!("{}{}", display, "0".to_string());
                }
                if button(ui, ".").clicked() {
                    *display = format!("{}{}", display, ".".to_string());
                }
                let button = egui::Button::new("=");
                let calculate = ui.add_sized(egui::Vec2 { x: 89.0, y: 40.0 }, button);
                if calculate.clicked() {
                    // TODO: Parse display string.
                    let lexer = Lexer::new(display);
                    let tokens = lexer.tokenize();
                    for token in tokens {
                        println!("{:?}", token);
                    }
                    display.clear();
                }
            });
        });
    }
}
