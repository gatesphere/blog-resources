package suschord.conway;

import processing.core.PMIDlet;

public class Conway extends PMIDlet {
  boolean[][] cells;
  boolean[][] oldcells;
  int cellsize;
  int live;
  int dead;
  
  public void setup() {
    live = color(255);
    dead = color(0);
    cellsize = 5;
    cells = new boolean[width / cellsize][height / cellsize];
    oldcells = cloneCells();
    
    background(dead);
    
    randomizeCells();
    
    //framerate(5);
    
    noStroke();
  }
  
  public void draw() {
    for (int i = 0; i < cells.length; i++) 
      for (int j = 0; j < cells[0].length; j++) {
        if(cells[i][j]) fill(live);
        else fill(dead);
        //point(i,j);
        rect(i*cellsize, j*cellsize, cellsize, cellsize);
      }
    
    iterate();
        
  }
  
  private void randomizeCells() {
    for (int i = 0; i < cells.length; i++) 
      for (int j = 0; j < cells[0].length; j++)
        cells[i][j] = (random(2) == 1);
  }
  
  private boolean[][] cloneCells() {
    boolean[][] x = new boolean[cells.length][cells[0].length];
    for (int i = 0; i < cells.length; i++) 
      for (int j = 0; j < cells[0].length; j++)
        x[i][j] = cells[i][j];
    return x;
  }
  
  private void iterate() {
    oldcells = cloneCells();
    for (int i = 0; i < cells.length; i++) 
      for (int j = 0; j < cells[0].length; j++) 
        cells[i][j] = cellAlive(i,j);
  }
  
  private boolean cellAlive(int x, int y) {
    // s23b3
    int neighbors = countNeighbors(x,y);
    if(cells[x][y] && neighbors >= 2 && neighbors <= 3) return true;
    if(!cells[x][y] && neighbors == 3) return true;
    return false;
  }
  
  private int countNeighbors(int x, int y) {
    int count = 0;
    count += liveInBounds(x-1, y-1);
    count += liveInBounds(x-1, y);
    count += liveInBounds(x-1, y+1);
    count += liveInBounds(x, y-1);
    count += liveInBounds(x, y+1);
    count += liveInBounds(x+1, y-1);
    count += liveInBounds(x+1, y);
    count += liveInBounds(x+1, y+1);
    return count;
  }
  
  private int liveInBounds(int x, int y) {
    if (x < 0) x = cells.length - 1;
    if (y < 0) y = cells[0].length - 1;
    if (x >= cells.length) x = 0;
    if (y >= cells[0].length) y = 0;
    if(oldcells[x][y]) return 1;
    return 0;
  }
}
