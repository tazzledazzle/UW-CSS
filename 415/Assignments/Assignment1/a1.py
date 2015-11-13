# Part A. Defining Functions (30 points). 
 
# Write Python function definitions for the following requirements (worth 5 points each, 
# except for numbers 2 and 4, which are worth 10 points each). You should be able to infer
# what each function should do by a combination of reading its name and examining the 
# relationship between its input and ouput on the given examples. Note that the functions 
# that accept lists as arguments must be able to handle lists of any length. 
# For this assignment your functions do not have to validate the types of 
# their inputs. That is, you may assume that they will be called with arguments of the proper types. 
 
# In problem 2, you may find it helpful to write a helping function that can translate
# one character, and you may find the various string methods to be useful: 
# islower() 
# isupper() 
# isdigit() 
# index()
# join(). 
# You might also consider using the functions map(), and list(). The mod operator ('%') may also be helpful.

import math

def main():
	print six_x_cubed_plus_5(2)
	print quadruples([2, 5, 1.5, 100, 3, 8, 7, 1, 1])
	print past_tense(['program', 'debug', 'execute', 'crash', 'repeat', 'eat'])
	print mystery_code("abc Iz th1s Secure? n0, no, 9!", 21)


# 1. six_x_cubed_plus_5(2) -> 53
def six_x_cubed_plus_5(num):
	return 6*math.pow(num,3) + 5

# 2. mystery_code("abc Iz th1s Secure? n0, no, 9!", 21) -> "twv5\o5a}$f5Fpv`gp*5{%95{z95,4"
def mystery_code(sentence, num):
	sen = ""
	for i in range(sentence.__len__()):
		sen += chr(ord(sentence[i]) + num)
		# sen += '\\'+ str(ord(sentence[i]))

	return sen

# 3. quadruples([2, 5, 1.5, 100, 3, 8, 7, 1, 1])  ->  [[2, 5, 1.5, 100], [3, 8, 7, 1], [1]]
def quadruples(list):
	sublist = []
	i = 0
	j = 4
	while j < list.__len__():
		sublist.append(list[i:j])
		i += 4
		j += 4

	if j - 4 < list.__len__():
		j = j - 4
		while j < list.__len__():
			sublist.append(list[j])
			j += 1

	return sublist

# 4. past_tense(['program', 'debug', 'execute', 'crash', 'repeat', 'eat']) ->
#  ['programmed', 'debugged', 'executed', 'crashed', 'repeated', 'ate']
# Use the following rules for forming the past tense of a regular verb in English: 
# (a) If the verb ends in 'e', add 'd'. (Example: 'execute' becomes 'executed'.) 
# (b) If the verb ends with a 'y' immediately preceded by a consonant, change the 'y' to 'i' and add 'ed'. 
# (Example: 'try' becomes 'tried'.) 
# (c) If the word ends in one vowel (not two vowels) followed by one consonant (but not 'y' or 'w'), 
# then repeat the consonant and add 'ed'. (Example: 'debug' becomes 'debugged'). 
# (d) For the irregular verbs to have, to be, to eat, and to go, handle these as special cases. 
# (e) In all other cases, add 'ed'. (Example: 'repeat' becomes 'repeated'.) You don't have to handle 
# irregular verbs other than those mentioned in (d). 
def past_tense(words):
	retensed = []
	for word in words:
		retensed.append(change_tense(word))

	return retensed

######### change_tense ###############
def change_tense(word):
	last_letter = word[word.__len__() - 1]
	second_to_last = word[word.__len__() - 2]
	if isIrregular(word):
		return irregular(word)
	elif last_letter == 'e':
		return word + 'd'
	elif last_letter == 'y' and not isVowel(second_to_last):
		return word[:word.__len__() - 2] + 'ied'
	elif isVowel(second_to_last) and not isVowel(last_letter) and not last_letter == 'y' and not last_letter == 'w' and not isVowel(word[word.__len__() - 3]):
		return word + last_letter + 'ed'
	else:
		return word + 'ed'

######### isIrregular ###############
# used in past_tense
def isIrregular(word):
	irregulars = ['have', 'be', 'eat', 'go']
	return word in irregulars

######### irregular ###############
# used in past_tense
def irregular(word):
	if word == 'have':
		return 'had'
	elif word == 'be':
		return 'ben'
	elif word == 'eat':
		return 'ate'
	elif word == 'go':
		return 'went'

######### isVowel ###############
# used in past_tense
def isVowel(letter):
	vowels = ['a', 'e', 'i', 'o', 'u']
	return letter in vowels



main()