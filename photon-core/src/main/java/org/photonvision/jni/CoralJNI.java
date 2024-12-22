package org.photonvision.jni;

import java.io.IOException;
import java.util.List;
import org.photonvision.common.util.TestUtils;

public class CoralJNI extends PhotonJNICommon {
    private boolean isLoaded;
    private static CoralJNI instance = null;

    private CoralJNI() {
        isLoaded = false;
    }

    public static CoralJNI getInstance() {
        if (instance == null) {
            instance = new CoralJNI();
        }

        return instance;
    }

    public static synchronized void forceLoad() throws IOException {
        TestUtils.loadLibraries();

        forceLoad(getInstance(), CoralJNI.class, List.of("rga", "coral", "coral_jni"));
    }

    @Override
    public boolean isLoaded() {
        return isLoaded;
    }

    @Override
    public void setLoaded(boolean state) {
        isLoaded = state;
    }
}