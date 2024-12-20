package org.photonvision.jni;

import java.awt.Color;
import java.lang.ref.Cleaner;
import java.util.List;
import java.util.concurrent.atomic.AtomicBoolean;
import org.opencv.core.Mat;
import org.opencv.core.Size;
import org.photonvision.common.logging.LogGroup;
import org.photonvision.common.logging.Logger;
import org.photonvision.common.util.ColorHelper;
import org.photonvision.vision.objects.Letterbox;
import org.photonvision.vision.objects.ObjectDetector;
import org.photonvision.vision.objects.CoralModel;
import org.photonvision.vision.pipe.impl.NeuralNetworkPipeResult;

public class CoralObjectDetector implements ObjectDetector {
    private static final Logger logger = new Logger(CoralObjectDetector.class, LogGroup.General);

    private final Cleaner cleaner = Cleaner.create();
    private AtomicBoolean released = new AtomicBoolean(false);

    private final long objPointer;
    
    private final CoralModel model;
    private final Size inputSize;

    @Override
    public CoralModel getModel() {
        return model;
    }

    public CoralObjectDetector(CoralModel model, Size inputSize) {
        this.model = model;
        this.inputSize = inputSize;

        objPointer = 1;
        
        logger.debug("Created detector for model " + model.modelFile.getName());

        cleaner.register(this, this::release);
    }

    @Override
    public List<String> getClasses() {
        return model.labels;
    }

    @Override
    public List<NeuralNetworkPipeResult> detect(Mat in, double nmsThresh, double boxTresh) {
        if (objPointer <= 0) {
            logger.error("Detecotr is not initialized! Model: " + model.modelFile.getName());
            return List.of();
        }

        Mat letterboxed = new Mat();
        Letterbox scale = 
                Letterbox.letterbox(in, letterboxed, this.inputSize, ColorHelper.colorToScalar(Color.GRAY));
        if (!letterboxed.size().equals(this.inputSize)){
            letterboxed.release();
            throw new RuntimeException("Letterboxed frame is not the right size!");
        }

        Object results = null;
        letterboxed.release();

        if (results == null) {
            return List.of();
        }

        return List.of();

        // return scale.resizeDetections(
        //     List.of(results).stream()
        //                 .map(it -> new NeuralNetworkPipeResult(it.rect, it.class_id, it.conf))
        //                 .toList()
        // );
    }

    @Override
    public void release() {
        if (released.compareAndSet(false, true)) {
            if (objPointer <= 0) {
                logger.error(
                    "Detector is not initialized, and so it can't be released! Model: " +
                    model.modelFile.getName()
                );
                return;
            }
        }

        logger.debug("Released detector for model " + model.modelFile.getName());
    }
}