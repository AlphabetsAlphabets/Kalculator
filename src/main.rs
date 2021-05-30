mod app;
use app::App;

mod parsing;

use egui;
use std::collections::HashMap;

fn spawn() {
    let app = App::default();
    let options = eframe::NativeOptions {
        initial_window_size: Some(egui::Vec2 { x: 300.0, y: 300.0 }),
        resizable: false,
        ..eframe::NativeOptions::default()
    };
    eframe::run_native(Box::new(app), options);
}

fn main() {
    spawn();
}
