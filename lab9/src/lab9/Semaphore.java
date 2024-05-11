package lab9;

public class Semaphore {
    
    private int value;

    public Semaphore(int value) {
        this.value = value;
    }
    
    /**
     * Increment the number of available resources.  This method never blocks.
     * It may wakeup a Thread waiting for the Semaphore. 
     */
    
    public synchronized void up(){
        if(this.value==0){
            notify();
        }
        this.value++;
    }
    
    /**
     * Request a resource. If no resources are available, the calling Thread
     * block until a resource controlled by the Semaphore becomes available.
     */
    
    public synchronized void down(){
        if(this.value==0){
            try {
                wait();
            }
            catch(InterruptedException e) {
                System.out.println("InterruptedException occured");
                }
        }
        this.value--;
    }
    
    public synchronized int availablePermits() {
        return value;
    }
}
