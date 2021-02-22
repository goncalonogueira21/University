import nltk
from nltk.stem import WordNetLemmatizer
lemmatizer = WordNetLemmatizer()

import numpy as np
import random
import json
import pickle

from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Activation, Dropout
from tensorflow.keras.optimizers import SGD


intents = json.loads(open('intents.json').read())

words =[]
classes = []
documents = []
ignore_letters =['?','!', ',', '.']

for intent in intents['intents']:
    for pattern in intent['patterns']:
        # pegar na frase e dividi-la pelas palavras
        word_list= nltk.word_tokenize(pattern)
        words.extend(word_list)
        documents.append((word_list, intent['tag']))
        if intent['tag'] not in classes:
            classes.append(intent['tag'])

# lemmatization
words =[lemmatizer.lemmatize(word) for word in words if word not in ignore_letters]

# tirar repetiçao e ordenar
words = sorted(set(words))

classes = sorted(set(classes))


# guardar as frases e classes
pickle.dump(words,open('words.pkl', 'wb'))
pickle.dump(classes,open('classes.pkl','wb'))

training=[]
output_empty=[0] * len(classes)


# toda a info passa para a lista training
for document in documents:
    bag=[]
    word_patterns = document[0]
    word_patterns = [lemmatizer.lemmatize(word.lower()) for word in word_patterns]
    for word in words:
        bag.append(1) if word in word_patterns else bag.append(0)

    output_row = list(output_empty)
    output_row[classes.index(document[1])] = 1
    training.append([bag,output_row])

# random e transformar num numpy array
random.shuffle(training)
training = np.array(training, dtype=object)

# criar x e y
train_x = list(training[:,0])
train_y = list(training[:,1])

# modelo neural network
model = Sequential()
model.add(Dense(128, input_shape=(len(train_x[0]),), activation='relu'))
model.add(Dropout(0.5))
model.add(Dense(64, activation='relu'))
model.add(Dropout(0.5))
model.add(Dense(len(train_y[0]), activation='softmax'))

sgd = SGD(lr=0.01, decay=1e-6, momentum=0.9, nesterov=True)
model.compile(loss='categorical_crossentropy', optimizer=sgd, metrics=['accuracy'])

hist = model.fit(np.array(train_x), np.array(train_y), epochs=300, batch_size=5, verbose=1)
model.save('chatbotmodel.h5', hist)

print("Done")


