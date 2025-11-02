package org.example.mindlauncher.controls;

import javafx.application.Platform;
import javafx.fxml.FXML;
import javafx.scene.Parent;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.layout.AnchorPane;

import java.util.Objects;

public class GameController {

    @FXML
    private Button ankrButton, vortexButton, exitButton;

    @FXML
    private AnchorPane main_pane;

    public void initialize() {
        ankrButton.setOnAction(e -> launchAnkr());
        vortexButton.setOnAction(e -> launchVortex());
        exitButton.setOnAction(e -> quitApp());
    }

    private void launchAnkr() {
        try {
            Parent view = javafx.fxml.FXMLLoader.load(Objects.requireNonNull(getClass().getResource("/org/example/mindlauncher/views/ankr-view.fxml")));
            main_pane.getChildren().setAll(view);
        } catch (Exception e) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error");
            alert.setHeaderText("Could not load the game view");
            alert.setContentText("ERROR: " + e.getMessage());
            alert.showAndWait();
            System.out.println(e.getMessage());
        }
    }

    private void launchVortex() {
        try {
            Parent view = javafx.fxml.FXMLLoader.load(Objects.requireNonNull(getClass().getResource("/org/example/mindlauncher/views/vortex-view.fxml")));
            main_pane.getChildren().setAll(view);
        } catch (Exception e) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error");
            alert.setHeaderText("Could not load the Vortex view");
            alert.setContentText("ERROR: " + e.getMessage());
            alert.showAndWait();
            System.out.println(e.getMessage());
        }
    }

    private void quitApp() {
        Platform.exit();
    }
}
