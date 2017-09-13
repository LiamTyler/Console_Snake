# Console Snake

## Description
This is a potential lab that I wrote for the students near the end of the semester. Now that they were more knowledgeable coders, I wanted to make a really enjoyable lab for them. I did a spin off of the classic 'Snake' arcade game. The focus on this lab was inheritance mostly. The students start out with just a snake moving around the screen. The write up walks them through hints to making a 'Fruit' class. When the snake eats a fruit, it should grow and get points. Then I have them build a 'MovingFruit' class, where the fruit randomly moves and is harder to eat. Then I have them refactor the three classes Snake, Fruit, and MovingFruit, by creating a parent 'Moveable' class, and having each class inherit from it. Lastly, they create an enemy by creating a 'SnakeFruit' class. Its both a snake that tries to beat you by eating the fruit first, but if you hit the head of the enemy snake, it acts like a fruit and you eat it for points. It actually works really well just by inheriting from both Snake and Fruit, and it doesnt take much work from the students. I just had to give them a single function (for targeting the fruit and moving) for the interest of time.

## Features
- Moveable Snake
- Graphics done all in terminal using ncurses library
- Fruit that moves around the screen randomly
- Eatable Enemy snake that tries to beat you to the fruit
- Adjustable features when you eat a fruit, such as speed up or grow

## Usage
The makefile will compile everything, including each new file you add, without having to be edited.
