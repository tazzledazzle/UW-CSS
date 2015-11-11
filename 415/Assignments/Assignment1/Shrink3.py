# Shrink3.py
# A conversational "doctor" simulation modelled loosely
# after J. Weizenbaum's ELIZA.
# This Python program goes with the book "The Elements of Artificial
# Intelligence".
# This version of the program runs under Python 3.x.

# Steven Tanimoto
# (C) 2012.

from re import *   # Loads the regular expression module.

def Shrink():
    'Shrink is the top-level function, containing the main loop.'
    print('They call me the Shrink.  Welcome to my sofa!')
    print('So what is your problem?')
    while True:
        the_input = input('TYPE HERE:>> ')
        if match('bye',the_input):
            print('Goodbye!')
            return
        wordlist = split(' ',remove_punctuation(the_input))
        # undo any initial capitalization:
        wordlist[0]=wordlist[0].lower()
        mapped_wordlist = you_me_map(wordlist)
        mapped_wordlist[0]=mapped_wordlist[0].capitalize()
        respond(the_input, wordlist, mapped_wordlist)

def respond(the_input, wordlist, mapped_wordlist):
    if wordlist[0]=='':
        print("Please say something.")
        return
    if wordlist[0:2] == ['i','am']:
        print("Please tell me why you are " +\
              stringify(mapped_wordlist[2:]) + '.')
        return
    if wpred(wordlist[0]):
        print("You tell me " + wordlist[0] + ".")
        return
    if wordlist[0:2] == ['i','have']:
        print("How long have you had " +\
              stringify(mapped_wordlist[2:]) + '.')
        return
    if wordlist[0:2] == ['i','feel']:
        print("I sometimes feel the same way.")
        return
    if 'because' in wordlist:
        print("Is that really the reason?")
        return
    if 'yes' in wordlist:
        print("How can you be so sure?")
        return
    if wordlist[0:2] == ['you','are']:
        print("Oh yeah, I am " +\
              stringify(mapped_wordlist[2:]) + '.')
        return
    if verbp(wordlist[0]):
        print("Why do you want me to " +\
              stringify(mapped_wordlist) + '?')
        return
    if wordlist[0:3] == ['do','you','think']:
        print("I think you should answer that yourself.")
        return
    if wordlist[0:2]==['can','you'] or wordlist[0:2]==['could','you']:
        print("Perhaps I " + wordlist[0] + ' ' +\
             stringify(mapped_wordlist[2:]) + '.')
        return
    if 'dream' in wordlist:
        print("For dream analysis see Freud.")
        return
    if 'love' in wordlist:
        print("All's fair in love and war.")
        return
    if 'no' in wordlist:
        print("Don't be so negative.")
        return
    if 'maybe' in wordlist:
        print("Be more decisive.")
        return
    if 'you' in mapped_wordlist or 'You' in mapped_wordlist:
        print(stringify(mapped_wordlist) + '.')
        return
    print(punt())

def stringify(wordlist):
    'Create a string from wordlist, but with spaces between words.'
    return ' '.join(wordlist)

punctuation_pattern = compile(r"\,|\.|\?|\!|\;|\:")    

def remove_punctuation(text):
    'Returns a string without any punctuation.'
    return sub(punctuation_pattern,'', text)

def wpred(w):
    'Returns True if w is one of the question words.'
    return (w in ['when','why','where','how'])

def dpred(w):
    'Returns True if w is an auxiliary verb.'
    return (w in ['do','can','should','would'])

PUNTS = ['Please go on.',
         'Tell me more.',
         'I see.',
         'What does that indicate?',
         'But why be concerned about it?',
         'Just tell me how you feel.']

punt_count = 0
def punt():
    'Returns one from a list of default responses.'
    global punt_count
    punt_count += 1
    return PUNTS[punt_count % 6]

CASE_MAP = {'i':'you', 'I':'you', 'me':'you','you':'me',
            'my':'your','your':'my',
            'yours':'mine','mine':'yours','am':'are'}

def you_me(w):
    'Changes a word from 1st to 2nd person or vice-versa.'
    try:
        result = CASE_MAP[w]
    except KeyError:
        result = w
    return result

def you_me_map(wordlist):
    'Applies YOU-ME to a whole sentence or phrase.'
    return [you_me(w) for w in wordlist]

def verbp(w):
    'Returns True if w is one of these known verbs.'
    return (w in ['go', 'have', 'be', 'try', 'eat', 'take', 'help',
                  'make', 'get', 'jump', 'write', 'type', 'fill',
                  'put', 'turn', 'compute', 'think', 'drink',
                  'blink', 'crash', 'crunch', 'add'])

Shrink() # Launch the program.
