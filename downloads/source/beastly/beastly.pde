// BEAST(LY)

Walker w;

void setup() {
  size(640, 360);
  background(0);
  noStroke();
  frameRate(15);
  w = new Walker();
}

void draw() {
  //background(0);
  fill(color(0, 32));
  rect(0,0,width, height);
  fill(color(255,0,32, random(127)));
  w.step();
  w.draw();
}

class Walker {
  int x, y;
  
  Walker() {
    x = width/2;
    y = height/2;
  }
  
  void step() {
    x += int(random(-15,15));
    y += int(random(-15,15));
    if (x < 0) x = 0;
    if (x > width) x = width;
    if (y < 0) y = 0;
    if (y > height) y = height;
  }
  
  void draw() {
    //println(x + " " + y);
    ellipse(x, y, 35, 35);
  }
}
