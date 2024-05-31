#include <Adafruit_LiquidCrystal.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int status = 0;
int on = -1;
float off = 0;
int index=0;
char code[5];

  
Adafruit_LiquidCrystal lcd(0);

typedef struct node{
  char c;
  struct node *right,*left;
}node;

struct node* MorseTree;
struct node* sym;

struct node *setNode(char c)
{
   struct node *n = (struct node*) malloc(sizeof(struct node));
   n->c = c;
   return n;
}

struct node* setRight(struct node *parent,char c)
{
   struct node *n = setNode(c);
   parent->right = n;
   return n;
}

struct node* setLeft(struct node *parent,char c)
{
   struct node *n = setNode(c);
   parent->left = n;
   return n;
}

void setTree()
{
    // free(MorseTree);
    MorseTree = setNode(' ');
    
    setRight(setRight(setRight(MorseTree,'T'),'M'),'O');
    setLeft(setLeft(setLeft(setLeft(MorseTree,'E'),'I'),'S'),'H');
    setRight(setRight(setRight(MorseTree->left,'A'),'W'),'J');
    setLeft(setLeft(setLeft(MorseTree->right,'N'),'D'),'B');
    setRight(setRight(MorseTree->right->left,'K'),'Y');
    setLeft(setLeft(MorseTree->right->right,'G'),'Z');
    setLeft(setLeft(MorseTree->left->right,'R'),'L');
    setLeft(setRight(MorseTree->left->left,'U'),'F');
    setRight(MorseTree->left->left->left,'V');
    setLeft(MorseTree->left->right->right,'P');
    setRight(MorseTree->right->left->left,'X');
    setLeft(MorseTree->right->left->right,'C');
    setRight(MorseTree->right->right->left,'Q');
}


/*char Get(char code[4])
{
 
  char codes[26][5] ={".-",
            "-...",
            "-.-.",
            "-..",
            ".",
            "..-.",
            "--.",
            "....",
            "..",
            ".---",
            "-.-",
            ".-..",
            "--",
            "-.",
            "---",
            ".--.",
            "--.-",
            ".-.",
            "...",
            "-",
            "..-",
            "...-",
            ".--",
            "-..-",
            "-.--",
                     "--.."};
  
  for (int i=0;i<26;i++)
  {
  		if(strcmp(code,codes[i])==0)
        {
         	 return 97+i;
        }
  }
  
}*/

void setup()
{
  lcd.begin(16, 2);
  pinMode(8, INPUT);
  Serial.begin(9600);
  setTree();
  sym = MorseTree;
}

void loop()
{
  status = digitalRead(8);
  //Serial.println(status);
  on += status;
  //off = (pow(off+2,1-status)-1);
  //off += (status-1)*-1;
  if(status==LOW && on>=0)
  {
    	off++;
    	if(off>=80)
        {
         	lcd.setCursor(index%16,(int) index/16);
          	lcd.print(sym->c);
          	sym = MorseTree;
          	index++;
          	on = -1;
          	off = 0;
        }
    	else if(off>=40 && on )
        {
          off = 0; 
          if( on<3 )
          {
            tone(7,1500,80);
          	sym = sym->left;
          }
          else 
          {
            tone(7,1500,200);
          	sym = sym->right;
          }
          on = 0;
        }
  }
  Serial.println(on);
    
  
  delay(100);
}

