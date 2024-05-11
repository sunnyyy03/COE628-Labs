package lab9;

public class Main {
    
    static final int philosopherCount = 5;
    static DiningPhilosophers[] diningPhilosophers = new DiningPhilosophers[philosopherCount];
    static Fork[] philosopherForks = new Fork[philosopherCount];
    
    public static void main(String argv[]) {
        for (int i = 0; i < philosopherCount; i++) {
            philosopherForks[i] = new Fork(i);
        }
        
        for (int i = 0; i < philosopherCount; i++) {
            Fork leftFork = philosopherForks[i];
            Fork rightFork = philosopherForks[(i + 1) % philosopherCount];
           
            diningPhilosophers[i] = new DiningPhilosophers(i, leftFork, rightFork);
        } 
        
        for (int p = 0; p < philosopherCount; p++) {
            Thread t = new Thread(diningPhilosophers[p]);
            t.start();
        }
        
        while(true) {
            try {
                Thread.sleep(1000);  
                
                boolean deadlock = true;
                for (Fork f : philosopherForks) {
                    if (f.isAvailable()) {
                        deadlock = false;
                        break;
                    }
                }
                
                if (deadlock) {
                    Thread.sleep(1000); 
                    System.out.println("Deadlock detected!");
                    System.exit(0); 
                }
                
                if (DiningPhilosophers.completed == philosopherCount) {
                    System.out.println("All philosophers have completed their dinner.");
                    System.exit(0); 
                }
                
            } catch (InterruptedException ex) {
                ex.printStackTrace(System.out);
                System.exit(1); 
            }
        }
    }
}
