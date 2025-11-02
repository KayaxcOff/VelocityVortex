package org.example.mindlauncher;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.stage.Stage;
import java.io.IOException;

public class Main extends Application {

    static final String LOGO_PATH = "C:\\Users\\muham\\Downloads\\mind_logo.jpg";

    public static void main(String[] args) {
        Application.launch(Main.class, args);
    }

    @Override
    public void start(Stage primaryStage) throws IOException {

        FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("views/main-view.fxml"));
        Image icon = new Image("file:" + LOGO_PATH);

        Scene primaryScene = new Scene(fxmlLoader.load());

        primaryStage.getIcons().add(icon);
        primaryStage.setTitle("Mind Launcher-v0.2");
        primaryStage.setScene(primaryScene);
        primaryStage.show();
    }
}
