package org.example.mindlauncher.controls;

import javafx.application.Platform;
import javafx.fxml.FXML;
import javafx.scene.Parent;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.layout.AnchorPane;

import java.io.IOException;
import java.util.Objects;
import java.util.Properties;

public class AnkrController {

    static final String GAME_PATH = "C:\\software\\Cpp\\projects\\Ankr\\cmake-build-debug-visual-studio\\Ankr.exe";

    @FXML
    private Button mainButton, launchButton, exitButton;

    @FXML
    private AnchorPane main_pane;

    public void initialize() {
        mainButton.setOnAction(e -> goToMain());
        launchButton.setOnAction(e -> launchGame());
        exitButton.setOnAction(e -> quitApp());
    }

    private void goToMain() {
        try {
            Parent view = javafx.fxml.FXMLLoader.load(Objects.requireNonNull(getClass().getResource("/org/example/mindlauncher/views/main-view.fxml")));
            main_pane.getChildren().setAll(view);
        } catch (IOException e) {
            throw new RuntimeException(String.valueOf(e));
        }
    }

    private void launchGame() {
        try {
            ProcessBuilder processBuilder = new ProcessBuilder(GAME_PATH);
            processBuilder.start();
        } catch (IOException e) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error");
            alert.setHeaderText("Could not launch the game");
            alert.setContentText("ERROR: " + e.getMessage());
            alert.setContentText("Please check the game path and try again.");
            alert.showAndWait();
            System.out.println(e.getMessage());
        }
    }

    private void quitApp() {
        Platform.exit();
    }
}
