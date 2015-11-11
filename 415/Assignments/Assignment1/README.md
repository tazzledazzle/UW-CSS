
# Assignment 1: Basics of Python and String Manipulation
#### CSE 415: Introduction to Artificial Intelligence
The University of Washington, Seattle, Spring 2015

The reading for this assignment is Python as a Second Language. 
Due Wednesday, April 8, through Catalyst CollectIt at 2:00 PM. 
 
You should turn in four files: (1) a file named a1.py of function definitions, (2) a file a1examplesplus.txt of example calls, results and answers to questions, (3) a file containing the Python code for your conversational agent, and (4) a text file containing a sample dialog between your agent and your partner's agent. For the file of examples, you can use a combination of input and output together with comment lines (beginning with a pound sign) to show that you have verified each of your answers on the computer. For each function, show a demonstration on the same example shown on this page, and two additional examples: one shorter (or smaller), and one longer (or larger) and more interesting (use your imagination). 
 
#### Part A. Defining Functions (30 points). 
 
Write Python function definitions for the following requirements (worth 5 points each, except for numbers 2 and 4, which are worth 10 points each). You should be able to infer what each function should do by a combination of reading its name and examining the relationship between its input and ouput on the given examples. Note that the functions that accept lists as arguments must be able to handle lists of any length. For this assignment your functions do not have to validate the types of their inputs. That is, you may assume that they will be called with arguments of the proper types. 
 
In problem 2, you may find it helpful to write a helping function that can translate one character, and you may find the various string methods to be useful: islower(), isupper(), isdigit(), index(), and join(). You might also consider using the functions map(), and list(). The mod operator ('%') may also be helpful.
1. six_x_cubed_plus_5(2) -> 53

2. mystery_code("abc Iz th1s Secure? n0, no, 9!", 21) -> "twv5\o5a}$f5Fpv`gp*5{%95{z95,4"

3. quadruples([2, 5, 1.5, 100, 3, 8, 7, 1, 1])  ->  [[2, 5, 1.5, 100], [3, 8, 7, 1], [1]]

4. past_tense(['program', 'debug', 'execute', 'crash', 'repeat', 'eat']) ->
 ['programmed', 'debugged', 'executed', 'crashed', 'repeated', 'ate']
Use the following rules for forming the past tense of a regular verb in English: (a) If the verb ends in 'e', add 'd'. (Example: 'execute' becomes 'executed'.) (b) If the verb ends with a 'y' immediately preceded by a consonant, change the 'y' to 'i' and add 'ed'. (Example: 'try' becomes 'tried'.) (c) If the word ends in one vowel (not two vowels) followed by one consonant (but not 'y' or 'w'), then repeat the consonant and add 'ed'. (Example: 'debug' becomes 'debugged'. (d) For the irregular verbs to have, to be, to eat, and to go, handle these as special cases. (e) In all other cases, add 'ed'. (Example: 'repeat' becomes 'repeated'.) You don't have to handle irregular verbs other than those mentioned in (d). 
#### Part B. Conversational Agents (70 points). 
 
Create a Python program that simulates a human character in a dialog. Your program should have some definable personality, such as a widget salesman, entertainment star, political figure, etc. Besides being able to carry on a conversation with a human user, it should be able to join into conversations with the agents created by any member of the class. To do this, it will need to implement certain functions with a strict protocol. 
 
Your solution should follow these guidelines:
You are welcome to use rules from the Shrink3.py program, but each rule must be modified so that the response will be different.
Incorporate a "memory" feature into your agent so that the conversation can return to some topic introduced earlier by the user. Make it work in a manner consistent with the character of your agent. (5 points).
Incorporate a "cycle" feature into your agent so that when a given rule fires repeatedly in a session, the response is not always the same but changes in a cyclical pattern. At least 2 of your agent's rules should use this feature with at least 2 alternative reponses each. (5 points)
Make up at least one rule that uses a random-choice feature to select a response form. (5 points)
There should be at least 15 rules in your program.
Your program should be ready to use as a module in another program that runs your agent with another agent in a dialog. The interface will consist of three functions that you need to write: one called introduce(), one called respond(theInput), and one called agentName(). 
 
The introduce() function should return a string representing a message that tells the name of the agent, what the agent represents and the name and UWNetID of you the programmer. For example, it might return a string containing:
My name is Rusty Sales, and I sell junky cars.
I was programmed by Jenny Chrysler. If you don't like
the way I deal, contact her at jchrysler@u.
How can I help you?
The respond function should work almost the same way as the one in Shrink3.py. But there are two important differences. First, the function will take one argument: the input string. It should compute the wordlist and mapped_wordlist values at the beginning of the function body instead of receiving those as inputs as in Shrink3.py. Second, instead of printing out its response, your respond function should return it as a string. This will allow the other agent to receive it as input in the joint-dialog program. 
 
The agentName function should return (as a string) a short nickname for your agent. This will be useful in printing out a prompt-like identifier when showing lines of a conversation among different agents. For example, the function might return Rusty for example above. 
 
You can test out your compliance to this interface by downloading the dialog.py and minimal agent programs.
Name your agent's Python file in the following way, so that we can keep track of the different agents: YourUWNetID.py, where YourUWNetID represents your UWNetID code (i.e., your email user name within the u.washington.edu domain. For one thing, this will guarantee that each of our agents is implemented in a file with a unique name. It will also give the graders an easy way to find your agent within a group, if needed.
Provide a comment in the code for each of your production rules.
In addition to your Python file, turn in a text file sampleConversation.txt that includes approximately 10 turns of the conversation for each agent, where Agent A is your agent and agent B is the agent of your partner. You can hand-edit the file with some comments -- ALL IN CAPS -- that point out places where your agent is using its memory feature, cycle feature, and random-choice feature. To help you create the conversation, you can use the dialog.py and Hearnone.py programs mentioned earlier.
