/**
 * Words. 
 * 
 * The text() function is used for writing words to the screen.
 * The letters can be aligned left, center, or right with the 
 * textAlign() function. 
 */

// The next line is needed if running in JavaScript Mode with Processing.js
/* @pjs font="Georgia.ttf"; */

String[] words = {
  "scandal",
  "sex",
  "violence",
  "rage",
  "rape",
  "terror",
  "death",
  "whore",
  "titties",
  "ass",
  "crotch",
  "affair",
  "anal lube",
  "cooter",
  "poon tang",
  "beef curtains",
  "cunnilingus",
  "Trex",
  "Mongolian Cluster Fuck",
  "punch it, Chewie!",
  "anal muffin",
  "twat waffle",
  "titfish",
  "deceit",
  "accusation",
  "murder",
  "homicide",
  "playful",
  "your mom",
  "the Inquirer",
  "Lindsey Lohan",
  "banned books",
  "Harry Potter",
  "The Bible",
  "The Qor'an",
  "Alistair Crowley",
  "Anton LeVey",
  "blackface",
  "rascism",
  "Nixon",
  "Clinton",
  "Malcolm X",
  "Caligula",
  "Genghis Khan",
  "Hitler",
  "R. Kelly",
  "Golden showers",
  "watersports",
  "two girls one cup",
  "BDSM",
  "torture",
  "waterboarding",
  "birth control",
  "abortion",
  "hate crimes",
  "the sky is pink",
  "2+2=5",
  "the new Star Wars trilogy",
  "Indiana Jones and the Kingdom of the Crystal Skull"
};

int variance_x, variance_y;

void setup() {
  size(1280, 600);
  background(255);
  // Create the font
  textFont(createFont("Georgia", 24));
  variance_x = width / 6;
  variance_y = height / 6;
  frameRate(15);
}

void draw() {
  fill(0,16);
  rect(0,0,width,height);
  pushMatrix();
  
  translate(random(-variance_x, variance_x), 
            random(-variance_y, variance_y));
  rotate(int(random(-2, 2)) * random(HALF_PI));
  textAlign(CENTER);
  drawType(width * 0.5, height * 0.5);
  popMatrix();
}

void drawType(float x, float y) {
  fill(color(random(255), random(255), random(255)));
  text(randomWord(), x, y);
}

String randomWord() {
  return words[int(random(words.length))];
}
