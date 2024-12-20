package org.photonvision.vision.objects;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.List;
import org.photonvision.jni.CoralObjectDetector;
import org.opencv.core.Size;

public class CoralModel implements Model {
    public final File modelFile;
    public List<String> labels;
    public final Size inputSize;

    public CoralModel(File modelFile, String labels) throws IllegalArgumentException, IOException {
        this.modelFile = modelFile;
        
        String[] parts = modelFile.getName().split("-");
        if (parts.length != 4) {
            throw new IllegalArgumentException("Invalid model file name: " + modelFile);
        }

        int width = Integer.parseInt(parts[1]);
        int height = Integer.parseInt(parts[2]);
        this.inputSize = new Size(width, height);

        try {
            this.labels = Files.readAllLines(Paths.get(labels));
        } catch (IOException e) {
            throw new IllegalArgumentException("Falied to read labels file " + labels, e);
        }
    }


    public String getName() {
        return modelFile.getName();
    }

    public ObjectDetector load() {
        return new CoralObjectDetector(this, inputSize);
    }

}