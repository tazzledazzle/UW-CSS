# Hearnone.py
# A minimal agent that can be used for basic testing of a dialog
# with another agent, using the dialog.py program.

def introduce():
    return """I'm Hearnone, designed by S. Tanimoto.
I don't pay much attention to what people say to me."""

def agentName():
    return "Hearnone"

from random import choice

def respond(the_input):
    attitude = choice(['like', 'tolerate', 'dislike', 'hate', 'love'])
    color = choice(['blue', 'pink', 'lavender', 'red', 'green', 'purple'])
    food = choice(['ice-cream', 'potatoes', 'carrots', 'quiche', 'burgers'])
    response = "Today I "+attitude+" "+color+" "+food+"."
    return response