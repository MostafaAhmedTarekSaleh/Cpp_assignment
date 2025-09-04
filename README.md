# MMU Digital Flashcard Interface

This is a **C++ console application** that provides a simple digital flashcard system with **user authentication, score tracking, and persistent storage of flashcards**.  
It is designed for students who want to practice Q&A style revision in an interactive way.

---

## ✨ Features
- **User Accounts**
  - Create a new user with a password.
  - Log in with existing credentials.
  - Track individual user scores.

- **Flashcards**
  - Add custom flashcards with a question and answer.
  - Review flashcards in order of **difficulty**, so hard questions appear first.
  - Difficulty automatically adjusts:
    - Correct answers → lower difficulty  
    - Wrong answers → higher difficulty  

- **Persistence**
  - Flashcards are saved to `sourcetext.txt`.
  - On startup, the program loads existing flashcards automatically.

- **Menu System**
