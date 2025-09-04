This is a C++ console application that provides a simple digital flashcard system with user authentication, score tracking, and persistent storage of flashcards.
It is designed for students who want to practice Q&A style revision in an interactive way.

Features:

-User Accounts

  -Create a new user with a password.
  
  -Log in with existing credentials.
  
  -Track individual user scores.

-Flashcards

  -Add custom flashcards with a question and answer.
  
  -Review flashcards in order of difficulty, so hard questions appear first.
  
  -Difficulty automatically adjusts:

  Correct answers → lower difficulty
  
  Wrong answers → higher difficulty

Persistence

  Flashcards are saved to sourcetext.txt.
  
  On startup, the program loads existing flashcards automatically.

Menu System

  Add a new flashcard
  
  Review flashcards
  
  Show your score
  
  Save flashcards to file
  
  Access/manage other users
  
  Show all cards (debugging/overview)
  
  Exit

📂 File Format

Flashcards are stored in a text file sourcetext.txt with the format:

question|answer


Example:

What is the capital of France?|Paris
2 + 2|4

Possible Improvements:

  Save/load users and scores between sessions.
  
  Allow skipping or exiting early during review.
  
  Support for more advanced flashcard formats (multiple-choice, hints).
  
  Stronger password handling (hashing instead of plain text).
