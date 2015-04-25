# Zepf_CSCI2270_FinalProject

Project Summary
---------------
This project is an attempt to create a database that will recommend movies for a community of users. Each user will rate movies that they have seen based on a five star scale. It will then compare their ratings with the rest of the users and it will find two other users they are most similar too. It will then recommend all the movies that the two similar users have rated 4 or 5 stars that the original user has not rated. The whole database will be concentrated in a class, the user database will be incorporated with a linked list, and the movie database will use a hash table belonging to each user.

How to Run
----------
The driver of this function gives you 8 options of how to run the program.
- 1. Add User - This function will prompt you for the name of a user and then adds that user to the database.
- 2. Add Rating - This function will prompt you for the name of the user who is rating, the name of the movie, and the rating the user will give on a scale of 0 to 5. It will then add this rating to the user's movie database.
- 3. Print Users - This function will print out all the users currently registered with the program.
- 4. Print User's Ratings - This function will prompt you for the name of a user and will then print out every rating that the user has entered.
- 5. Find Matches - This function will prompt you for the name of a user and will print out the two most similar users to the original user. You must run this option before you can find movie recommendations.
- 6. Find Recommendations - This function will prompt you for the name of the user and will print out every movie that their two matches have rated a 4 or 5 that the original user hasn't seen. 
- 7. AutoFill Library - This function will automatically add five users who each have five ratings to the database.
- 8. Quit - This option will terminate the program.

Dependencies
------------
This program has no requirements to run. As long as you can run a C++ program, this program should have no problem.

System Requirements
-------------------
This program has no system requirements. As long as you can run a C++ program, this program should have no problem.

Group Members
-------------
Joshua Zepf

Contributors
------------
Joshua Zepf

Open Issues/Bugs
----------------
- For large databases, the "findMatches" function takes a very long time. This is because it has to compare every movie in the original user's database to every movie in every other user's database. 
- There are no functions to delete or change users
- There are no functions to delete or change ratings
- On some very rare occasions, it will recommend a movie to a user that they have already seen. For example, in the autofilled database, it will recommend "Moneyball" to Chase and Max even though they have both seen it.
- The autofill feature only puts in 5 users and 25 ratings, so to make the autofill more effective, there could be more entries.
