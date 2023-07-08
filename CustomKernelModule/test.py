#Question 4

import random

L = ['Abuse', 'Adult', 'Agent', 'Anger', 'Apple', 'Award', 'Basis', 'Beach', 'Birth', 'Block', 'Blood', 'Board', 'Brain', 'Bread', 'Break', 'Brown', 'Buyer', 'Cause', 'Chain', 'Chair', 'Chest', 'Chief', 'Child', 'China', 'Claim', 'Class', 'Clock', 'Coach', 'Coast', 'Court', 'Cover', 'Cream', 'Crime', 'Cross', 'Crowd', 'Crown', 'Cycle', 'Dance', 'Death', 'Depth', 'Doubt', 'Draft', 'Drama', 'Dream', 'Dress', 'Drink', 'Drive', 'Earth', 'Enemy', 'Entry', 'Error', 'Event', 'Faith', 'Fault', 'Field', 'Fight', 'Final', 'Floor', 'Focus', 'Force', 'Frame', 'Frank', 'Front', 'Fruit', 'Glass', 'Grant', 'Grass', 'Green', 'Group', 'Guide', 'Heart', 'Henry', 'Horse', 'Hotel', 'House', 'Image', 'Index', 'Input', 'Issue', 'Japan', 'Jones', 'Judge', 'Knife', 'Laura', 'Layer', 'Level', 'Lewis', 'Light', 'Limit', 'Lunch', 'Major', 'March', 'Match', 'Metal', 'Model', 'Money', 'Month', 'Motor', 'Mouth', 'Music', 'Night', 'Noise', 'North', 'Novel', 'Nurse', 'Offer', 'Order', 'Other', 'Owner', 'Panel', 'Paper', 'Party', 'Peace', 'Peter', 'Phase', 'Phone', 'Piece', 'Pilot', 'Pitch', 'Place', 'Plane', 'Plant', 'Plate', 'Point', 'Pound', 'Power', 'Press', 'Price', 'Pride', 'Prize', 'Proof', 'Queen', 'Radio', 'Range', 'Ratio', 'Reply', 'Right', 'River', 'Round', 'Route', 'Rugby', 'Scale', 'Scene', 'Scope', 'Score', 'Sense', 'Shape', 'Share', 'Sheep', 'Sheet', 'Shift', 'Shirt', 'Shock', 'Sight', 'Simon', 'Skill', 'Sleep', 'Smile', 'Smith', 'Smoke', 'Sound', 'South', 'Space', 'Speed', 'Spite', 'Sport', 'Squad', 'Staff', 'Stage', 'Start', 'State', 'Steam', 'Steel', 'Stock', 'Stone', 'Store', 'Study', 'Stuff', 'Style', 'Sugar', 'Table', 'Taste', 'Terry', 'Theme', 'Thing', 'Title', 'Total', 'Touch', 'Tower', 'Track', 'Trade', 'Train', 'Trend', 'Trial', 'Trust', 'Truth', 'Uncle', 'Union', 'Unity', 'Value', 'Video', 'Visit', 'Voice', 'Waste', 'Watch', 'Water', 'While', 'White', 'Whole', 'Woman', 'World', 'Youth']
#Above List has 212 5-leter words

word = L[random.randint(0,(len(L)-1))]
word = word.lower()
word="refer"
print(word)

count = 0
while count < 6:
    guess = input("Enter your guess: ")
    guess = guess.lower()

    if len(guess) != 5:
        print("Enter a 5-letter word.")
        continue
    else:
        count+=1
    
    if word == guess:
        print(f"The word is {word}.",end=" ")
        print(f"Congrats, you successfully guessed the word in {count} tries.")
        break

    if count == 6 and word != guess:
        print(f"You have used up all your tries. The correct word was {word}.")
        break

    guessPlaceTrue = []
    for i in range(0,5):
        if word[i]==guess[i]:
            print(word[i],end='')
            guessPlaceTrue.append(word[i])
        else:
            print("-",end='')
    
    guessPlaceFalse = []
    for i in range(0,5):
        # if word[i] == guess[i]:
        #     pass
        if guess[i] in word:
            if word.index(guess[i]) != i and word.count(guess[i]) > (guessPlaceFalse.count(guess[i]) + guessPlaceTrue.count(guess[i])):
                guessPlaceFalse.append(guess[i])

    if len(guessPlaceFalse) > 0:
        print()
        print("Other characters present: ", end = "")
        for j in guessPlaceFalse:
            print(j, end = " ")
    print()