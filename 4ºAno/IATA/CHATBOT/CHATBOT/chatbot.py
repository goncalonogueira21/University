import random
import json
import pickle
import numpy as np


import nltk
from nltk.stem import WordNetLemmatizer

from nrclex import NRCLex

from tensorflow.keras.models import load_model

from tkinter import *
root = Tk()

lemmatizer = WordNetLemmatizer()
intents = json.loads(open('intents.json').read())

#carrega palavras guardadas do ficheiro json lido para treinar o bot
words = pickle.load(open('words.pkl', 'rb'))
classes = pickle.load(open('classes.pkl', 'rb'))
model = load_model('chatbotmodel.h5')
message=""

def clean_up_sentence(sentence):
    sentence_words = nltk.word_tokenize(sentence)
    sentence_words = [lemmatizer.lemmatize(word) for word in sentence_words]
    return sentence_words


def bag_of_words(sentence):
    sentence_words = clean_up_sentence(sentence)
    bag = [0] * len(words)
    for w in sentence_words:
        for i, word in enumerate(words):
            if word == w:
                bag[i] = 1
    return np.array(bag)

#prevê emoção da frase de input
def predict_emotion(sentence):
    with open('logger.txt', 'a') as f:
        word_list = nltk.word_tokenize(sentence)
        for i in range(len(word_list)):
            emotion = NRCLex(word_list[i])
        emo = emotion.top_emotions
        emo2 = emo[0][1]
        if emo2 > 0.3:
            f.write(sentence + ' (' + emo[0][0] + ')' + '\n')
        else:
            f.write(sentence + ' ' + '(neutral)' + '\n')

#preve a que classe pertence a frase do input
def predict_class(sentence):
    bow = bag_of_words(sentence)
    res = model.predict(np.array([bow]))[0]
    ERROR_THRESHOLD = 0.3
    results = [[i, r] for i, r in enumerate(res) if r > ERROR_THRESHOLD]

    results.sort(key=lambda x: x[1], reverse=True)
    return_list = []
    for r in results:
        return_list.append({'intent': classes[r[0]], 'probability': str(r[1])})
    return return_list

#consoante a classe devolve uma resposta random dessa classe
def get_response(intents_list, intents_json):
    tag = intents_list[0]['intent']
    list_of_intents = intents_json['intents']
    for i in list_of_intents:
        if i['tag'] == tag:
            result = random.choice(i['responses'])
            break
    return result

#resumos da conversa
def resumo_conversa():
    file = open('logger.txt', 'r')
    data = file.read()
    occurrences_fear = data.count("fear")
    occurrences_anger = data.count("anger")
    occurrences_anticipation = data.count("anticipation")
    occurrences_trust = data.count("trust")
    occurrences_surprise = data.count("surprise")
    occurrences_positive = data.count("positive")
    occurrences_negative = data.count("negative")
    occurrences_sadness = data.count("sadness")
    occurrences_disgust = data.count("disgust")
    occurrences_joy = data.count("joy")
    occurrences_neutral = data.count("neutral")
    num_lines = sum(1 for line in open('logger.txt'))
    chatWindow.insert(END, "\n" + 'Resumo da conversa: ')
    chatWindow.insert(END, "\n" + str(num_lines) + ' Mensagens enviadas')
    if occurrences_fear > 0: chatWindow.insert(END, "\n"+ str(occurrences_fear) + ' Frase(s) com medo')
    if occurrences_anger > 0: chatWindow.insert(END, "\n"+ str(occurrences_anger) + ' Frase(s) zangadas')
    if occurrences_anticipation > 0: chatWindow.insert(END, "\n"+ str(occurrences_anticipation) + ' Frase(s) ansiosas')
    if occurrences_trust > 0: chatWindow.insert(END, "\n"+ str(occurrences_trust) + ' Frase(s) confiantes')
    if occurrences_surprise> 0: chatWindow.insert(END, "\n"+ str(occurrences_surprise) + ' Frase(s) surpresas')
    if occurrences_positive > 0: chatWindow.insert(END, "\n"+ str(occurrences_positive) + ' Frase(s) positivas')
    if occurrences_negative > 0: chatWindow.insert(END, "\n"+ str(occurrences_negative) + ' Frase(s) negativas')
    if occurrences_sadness > 0: chatWindow.insert(END, "\n"+ str(occurrences_sadness) + ' Frase(s) tristes')
    if occurrences_disgust > 0: chatWindow.insert(END, "\n"+ str(occurrences_disgust) + ' Frase(s) repulsivas')
    if occurrences_joy > 0: chatWindow.insert(END, "\n"+ str(occurrences_joy) + ' Frase(s) alegres')
    if occurrences_neutral > 0:  chatWindow.insert(END, "\n"+ str(occurrences_neutral) + ' Frase(s) neutras')


print("GO! Bot is running!")

# apagar tudo o que tava no logger
f = open('logger.txt','w')
f.close()



def sendYou():

   message = messageWindow.get("1.0" ,'end-1c')
   sendYou = "You : " + message
   chatWindow.insert(END, "\n"+ sendYou)
   if message == "quit":
       resumo_conversa()
       chatWindow.yview(END)
   else:
    predict_emotion(message)
    ints = predict_class(message)
    # saida
    res = get_response(ints, intents)
    sendBot = "Bot : " + res
    chatWindow.insert(END, "\n" + sendBot)
    chatWindow.yview(END)
    messageWindow.delete('1.0', END)


def sendYouEnter(event):

   message = messageWindow.get("1.0" ,'end-1c').rstrip()
   sendYou = "You : " + message
   chatWindow.insert(END, "\n"+ sendYou)
   if message == "quit":
       resumo_conversa()
       chatWindow.yview(END)
   else:
    predict_emotion(message)
    ints = predict_class(message)
    # saida
    res = get_response(ints, intents)
    sendBot = "Bot : " + res
    chatWindow.insert(END, "\n" + sendBot)
    chatWindow.yview(END)
    messageWindow.delete('1.0', END)


# window title
root.title('Chat Bot')

# window size
root.geometry('400x500')

#add scrollbar
scrollbar = Scrollbar(root)
scrollbar.place(x=375, y=5, height=385)

# create chat window
chatWindow = Text(root, bd=1, bg='black', width = 50, height = 8, fg='white', yscrollcommand=scrollbar.set)
chatWindow.place(x=6, y=6, height=385, width=370)

scrollbar.config(command= chatWindow.yview)

#Create messageWindow
messageWindow = Text(root, bg='black', width=30, height=4, fg='white')
messageWindow.place(x=120, y=400, height=88, width=260)

#Create enter button
Button = Button(root, text='send', bg='white', activebackground='light blue', width=12, height=5, font=('Arial', 20), command=sendYou)
Button.place(x=6, y=400, height=88, width=115)

chatWindow.insert(END, "GO! Bot is running!")
root.bind('<Return>', sendYouEnter)
root.mainloop()

