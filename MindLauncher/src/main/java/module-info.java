module org.example.mindlauncher {
    requires javafx.controls;
    requires javafx.fxml;
    requires javafx.graphics;

    opens org.example.mindlauncher.controls to javafx.fxml;
    opens org.example.mindlauncher to javafx.fxml;
    exports org.example.mindlauncher;
}