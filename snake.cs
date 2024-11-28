using System;
using System.Collections.Generic;
using System.Linq;

class SnakeGame
{
    Random rnd = new Random();
    int appleX, appleY;

    int countApple = 1;

    const int LIMITx = 21;
    const int LIMITy = 21;

    List<(int x, int y)> SnakeBody = new List<(int, int)>(); // Stores snake body positions
    int Direction = 2; // Default direction: 2 - Right

    string[,] Board = new string[LIMITx, LIMITy];

    public SnakeGame()
    {
        SnakeBody.Add((1, 1)); // Initialize snake position
        RndApple(); // Initialize apple position
    }

    void SetDirection(char direction) // Get direction based on user input (WASD)
    {
        switch (direction)
        {
            case 'W': Direction = 3; break; // Up
            case 'A': Direction = 1; break; // Left
            case 'S': Direction = 4; break; // Down
            case 'D': Direction = 2; break; // Right
        }
    }

    void SetSnakeOnBoard()
    {
        // Calculate new head position
        (int headX, int headY) = SnakeBody.First();
        (int newX, int newY) = Direction switch
        {
            1 => (headX, headY - 1), // Left
            2 => (headX, headY + 1), // Right
            3 => (headX - 1, headY), // Up
            4 => (headX + 1, headY), // Down
            _ => (headX, headY)
        };

        // Check collision with walls or self
        if (newX <= 0 || newX >= LIMITx - 1 || newY <= 0 || newY >= LIMITy - 1 || SnakeBody.Contains((newX, newY)))
        {
            Console.WriteLine("Game Over!");
            Environment.Exit(0);
        }

        // Add new head position to the snake
        SnakeBody.Insert(0, (newX, newY));

        // Check if apple is eaten
        if (newX == appleX && newY == appleY)
        {
            RndApple(); // Generate new apple
            countApple++;
            setOGapple();
        }
        else
        {
            SnakeBody.RemoveAt(SnakeBody.Count - 1); // Remove tail if no apple eaten
        }
    }

    public void RndApple()
    {
        // Generate a new random apple position
        do
        {
            appleX = rnd.Next(1, LIMITx - 1);
            appleY = rnd.Next(1, LIMITy - 1);
        } while (SnakeBody.Contains((appleX, appleY))); // Ensure apple doesn't spawn on snake
    }

    public void SetBoard()
    {
        for (int i = 0; i < LIMITx; i++)
        {
            for (int j = 0; j < LIMITy; j++)
            {
                if (i == 0 || i == LIMITx - 1)
                {
                    Board[i, j] = "-"; // Top and bottom borders
                }
                else if (j == 0 || j == LIMITy - 1)
                {
                    Board[i, j] = "|"; // Left and right borders
                }
                else
                {
                    Board[i, j] = " "; // Empty spaces inside the board
                }
            }
        }

        // Set apple position
        Board[appleX, appleY] = "A";

        // Update snake positions
        foreach (var part in SnakeBody)
        {
            Board[part.x, part.y] = "O";
        }
    }

    public void PrintBoard()
    {
        Console.Clear(); // Clear console for smooth gameplay
        SetBoard(); // Update the board before printing
        for (int i = 0; i < LIMITx; i++)
        {
            for (int j = 0; j < LIMITy; j++)
            {
                Console.Write(Board[i, j]);
            }
            Console.WriteLine(); // Move to the next line after each row
        }
    }

    int OGspeed = 250;

    void setOGapple()
    {
        int minusTo = countApple * 10;

        if(OGspeed-minusTo >= 100)
        {
            OGspeed -= minusTo;
        }
    }

    public void PlayGame()
    {
        ConsoleKeyInfo keyInfo;

        while (true)
        {
            // Non-blocking user input
            if (Console.KeyAvailable)
            {
                keyInfo = Console.ReadKey(true);
                char key = char.ToUpper(keyInfo.KeyChar);
                SetDirection(key);
            }

            SetSnakeOnBoard();
            PrintBoard();
            System.Threading.Thread.Sleep(OGspeed); // Adjust speed of the game
        }
    }

    static void Main(string[] args)
    {
        SnakeGame game = new SnakeGame();
        game.PlayGame();
    }
}
