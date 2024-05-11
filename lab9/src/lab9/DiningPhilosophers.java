package lab9;

import java.util.concurrent.ThreadLocalRandom;

public class DiningPhilosophers extends Thread {
    int philosopherNumber;
    Fork leftFork;
    Fork rightFork; 
    static int completed = 0;
    
    public DiningPhilosophers(int num, Fork left, Fork right){
        this.philosopherNumber = num;
        this.leftFork = left;
        this.rightFork = right;       
    }
    
    @Override
    public void run() {
        while(true){
            ponder();
            leftFork.takeFork(); 
            System.out.println(" Fork " + leftFork.getId() + " taken by Philosopher " + (philosopherNumber + 1));    
            rightFork.takeFork();
            System.out.println(" Fork " + rightFork.getId() + " taken by Philosopher " + (philosopherNumber + 1));    
            dine();
            System.out.println(" Philosopher " + (philosopherNumber + 1) + " completed his dinner");    
            leftFork.releaseFork();
            System.out.println(" Philosopher " + (philosopherNumber + 1) + " released fork " + leftFork.getId());  
            rightFork.releaseFork();
            System.out.println(" Philosopher " + (philosopherNumber + 1) + " released fork " + rightFork.getId());  
            
            synchronized (DiningPhilosophers.class) {
                completed++;
            }
            
            System.out.println("Till now number of philosophers completed dinner are " + completed);
            
            if(completed == Main.philosopherCount){
                System.out.println("All philosophers have completed their dinner.");
                break;
            }
            
            ponder(); 
        }
    }
    
    void ponder() {
        int sleepTime = ThreadLocalRandom.current().nextInt(0, 1000);
        try {
            Thread.sleep(sleepTime);            
        } catch (InterruptedException ex) {
            ex.printStackTrace(System.out);
        }
    }
    
    void dine() {
        int sleepTime = ThreadLocalRandom.current().nextInt(0, 1000);
        try {
            Thread.sleep(sleepTime);
        } catch (InterruptedException ex) {
            ex.printStackTrace(System.out);
        }
    }
}
