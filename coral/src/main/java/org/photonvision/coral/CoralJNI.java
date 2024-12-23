package org.photonvision.coral;


public class CoralJNI {
   static {
      System.loadLibrary("CoralJNI"); // Load native library hello.dll (Windows) or libhello.so (Unixes)
                                   //  at runtime
                                   // This library contains a native method called sayHello()
   }
 
   // Declare an instance native method sayHello() which receives no parameter and returns void
   private native void sayHello();
 
   // Test Driver
   public static void main(String[] args) {
      new CoralJNI();  // Create an instance and invoke the native method
   }


    private long objPointer;

    private native long create();
    private native long destory(long objPointer);

    private native int[] detect(long detectorPtr, long imagePtr, double nmsTresh, double boxTresh);

    public static native boolean checkIfTPUConnected();

    public CoralJNI() {
        this.objPointer = create();
    }

    public synchronized void deleteCoral() {
        if (this.objPointer != 0) {
            destory(this.objPointer);
            this.objPointer = 0;
        }
    }
    

    @Override
    protected void finalize() throws Throwable {
        deleteCoral();
        super.finalize();
    }
}