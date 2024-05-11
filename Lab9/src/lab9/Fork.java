package lab9;

public class Fork {
    Semaphore semaphore = new Semaphore(1);
    int id; 
    
    public Fork(int id){
        this.id = id;
    }
     
    int getId() {
        return id + 1;
    }
     
    void takeFork() {
        semaphore.down();
    }
    
    void releaseFork(){
        semaphore.up();
    }
        
    boolean isAvailable(){
        return semaphore.availablePermits() > 0;
    }
}
