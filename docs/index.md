# Overview

Everything that is explain here have to be wrote on your ./data/data.json file.

Before creating your story you have to put some [essential settings keys](#settings) on your data.json

When you are done with those essential settings keys you can begin [creating your story](#create-story) !

# Table of content

- [Settings](#settings)
  - [Languages](#languages)
  - [Languages code](#languages-code)
  - [Default language](#default-language)
  - [Menu](#menu)
  - [Menu in other language](#menu-other-language)
  - [Menu drawing position](#menu-drawing-position)
 
- [Story](#story)
  - [Create story](#create-story)
  - [Create story in other language](#story-other-language)
  - [Create chapter](#create-chapter)
  - [Select chapter's entry part](#chapter-entry-part)
  - [Create part](#create-part)
    + [Add next key](#Add-next-key)
    + [Add date](#add-date)
    + [Add upgrade](#add-upgrade)
    + [Add choices](#add-choices)
    + [Add test](#add-test)

---

# Settings

Settings keys are simple keys that must be added to make the game playable.


## Languages

You can set as much language as you want using "languages" key.

languages is a key that take an array of strings as value.


```
  "languages": ["English", "Francais"]
```


In this example, "languages" key define two language which is "English" and "Francais".

To continue with languages, you have to link each language to its content with a [language code](#languages-code).


### Languages-code

You have to set your languages to its content using "languages_code" key.

languages_code is a key that take an array of strings as value.


```
  "languages": ["English", "Francais"]
  "languages_code": ["", "fr"]
```


In this example, "languages_code" key define two languages code which is "" and "fr"
* "English" language is linked to "" language_code, meaning that "English" language is linked to content: "menu" and "story"
* "Francais" language is linked to "fr" language_code, meaning that "Francais" language is linked to content: "menu_fr" and "story_fr"

I recommand using an empty string for your default language.
Unlinked language will be linked to the [default language](#default-language).


## Default-language

You can set your default language using "default_language" key. You have to choose your default language between every language that you put on your [languages](#languages) key.

default_language is a key that take a string as value.


```
  "languages": ["English", "Francais"]
  "default_language": "English"
```


In this example, "default_language" key define "English" language as default one.


## Menu

You have to set your [default language](#default-language) menu's options content using "menu" key.

menu is a key that take an array of strings as value.

The array must contain five strings
* The first string define the option to play the game
* The second string define the option to play a mini-game
* The third string define the option to choose an other language
* The fourth string define the option to show credits
* The fifth string define the option to quit the game


```
  "menu": ["Story", "Mini-game", "Language", "Credits", "Quit"]
```


If you have other languages, your must create a [menu key for other language]().


## Menu-other-language

Works the same as [menu key](#menu-key), but has to be named differently.

You have to put the [language code](#languages-code) right after the key separated by an underscore.


```
  "languages": ["English", "Francais"]
  "languages_code": ["", "fr"]
  "menu_fr": ["Histoire", "Mini-jeu", "Langue", "Credits", "Quitter"]
```


In this example, "menu_fr" key is a menu for the language "Francais" which has "fr" as [language code]().


## Menu-drawing-position

You can set your drawing menu position using "menu_drawing_position" key.
The drawing is the ./data/menu_drawing file, there is an ASCII Art example but you can put whatever you want on it.

menu_drawing_position is a key that take an int as value.

* To disable the drawing set value to 0
* To position it at the top of the menu set value to 1
* To position it on the right of the menu set value to 2
* To position it at the bottom of the menu set value to 3
* To position it on the left of the menu set value to 4


```
  "menu_drawing_position": 1
```


In this example, the drawing will be placed at the top of the menu.


## Name-size

You can set a maximum amount of characters for player's name using "max_name_size".

max_name_size is a key that take an int as value.

```
  "max_name_size": 10
```


In this example, "max_name_size" key define the maximum amount of characters for the player's name to 10 letters.


## Set-challenge-time

You can modify the time that each bar of the loading bar take to be completed during an agility test using "agility_speed" key.

agility_speed is a key that take an int as value, value is in microseconds.


```
  "agility_speed": 100000
```


In this example, "agility_speed" key define the time taken to charge a bar to 0,1 sec.


## Text-speeds

You can modify the time that each letter take to be printed using "text_speed_0" key and "text_speed_1" key when the player skipped.

text_speed_0 and "text_speed_1" are keys that take an int as value, value is in microseconds.


```
  "text_speed_0": 10000,
  "text_speed_1": 1000,
```


In this example, "text_speed_0" key define the time taken to write a letter to 0,01 second and "text_speed_1" key define the time taken to write a letter when player skipped to 0,001 second


## Credits

You can put your name in game's credits using the "story_writer" key.

story_writer is a key that take a string as value.


```
  "story_writer": "Henrie"
```


In this example, "story_writer" key define the story writer name to "Henrie".


# Story

Make sure to have every [essential settings keys](#settings) on your data.json before creating your story

When you are done with those essential settings keys you can begin [creating your story](#create-story) !


## Create-story

To create a story, you have to create a key named "story", this key is going to be the story for the default language.
To create a story for an other language, look [this](#story-other-language)

```
"story": [

]
```


To continue writing your story, you have to [create a chapter](#create-chapter).


### Story-other-language

To create a story on other language than the default one, you have to put the [language code](#languages-code) right after the key separated by an underscore.

```
"story_fr": [

]
```

To continue writing your story in this language, you have to [create a chapter](#create-chapter).


## Create-chapter

To create a chapter, you have to create a key named as your chapter is titled in the story key.

```
"story": [
  {
    "Introduction": [
 
    ]
  }
]
```


Adding a new chapter works the same for others languages stories.

To continue writing your story, you have to [create a part](#create-part).


## Chapter-entry-part

You have to put your desired first part's key using "entry_keys" key.
First string is the key of the part that will be loaded firstly in the first chapter, second string is the key of the part that will be loaded firstly in the second chapter, etc.

entry_keys is a key that take an array of strings as value.

Note that this key has to be in the root of your data.json file, not inside of story key.


```
  "entry_keys": ["intro_1", "battle_1"]
```


In this example, "entry_keys" key define the first part's key "intro_1" to be loaded firstly for the first chapter and "battle_1" for the second chapter.

Note that "entry_keys" key is the same for every language.


## Create-part

In your data.json, create an object in the desired chapter, the position is not important.

The object take atleast two strings
* A string named "key" that is the id of the part.
* A string named "text" that is the text to display on player's screen.

Note that you have to add your first part's key for each chapter in the [entry_keys key](#chapter-entry-part) in the settings.
Note that you the game can only display ASCII characters, so pay attention writting characters on the "text" key on your part.

```
"story": [
  {
    "Introduction": [
      {
        "key": "This is the part id",
        "text": "This string is going to be displayed on player's screen"
      }
    ]
  }
]
```

You can also add a [following part to your part](#add-next-key), [modify current story date](#add-date), [upgrade player skills](#add-upgrade), [confront player to a choice](#add-choices) and [challenge player's skills](#add-test).


### Add-next-key

You can set a linear next part that will be loaded right after your current part using "next_key" key.

next_key is a key that take a string as value.

Note that you can't combine next_key with [choices](#add-choices) or [test](#add-test).

```
"story": [
  {
    "Introduction": [
      {
        "key": "intro_1",
        "text": "This is the first text",
        "next_key": "intro_2"
      },
      {
        "key": "intro_2",
        "text": "This is the first text"
      }
    ]
  }
]
```


In this example, "intro_1" part is firstly loaded and right after "intro_2" part is loaded too because of intro_1's next_key.


### Add-date

You can set a linear next part that will be loaded right after your current part using "next_key" key.
You can modify current story date using "date" key, the date will be displayed on the top left of the player's screen.

The object take three datas
* An int named "day" that define the day number.
* A string named "month" that define the month name.
* An int named "year" that define the year number.


```
"story": [
  {
    "Introduction": [
      {
        "key": "intro_1",
        "text": "The story begin on 18 August 1980.",
        "date": {
          "day": 18,
          "month": "August",
          "year": 1980
        }
      }
    ] 
  }
]
```


### Add-upgrade

You can upgrade a player skill using "choices" key.

The object take two strings
* A string named "skill_type" that is the skill that you want to upgrade.
* An int named "add_value" that is the value you want to add.


```
"story": [
  {
    "Introduction": [
      {
        "key": "intro_1",
        "text": "This part is decrementing agility skill by 2",
        "upgrade": {
          "skill_type": "agility",
          "add_value": -2
        }
      }
    ]
  }
]
```


In this example, "intro_1" part is decrementing agility player skill by 2.

Note that you can increment a skill by writing positive value on "add_value"


### Add-choices

You can confront the player to a choice using "choices" key.

choices is a key that take an array of objects as value

Each object take two strings
* A string named "text" that is the text of a choice.
* A string named "next_key" that is the following part of a choice.

Note that you can't combine choices with [next_key](#add-next-key) or [test](#add-test).

Note that you can put a maximum of six object in the choices key, if you add more object, choices could be displayed badly.

Note that you the game can only display ASCII characters, so pay attention writting characters on the "text" key on your choice object.


```
"story": [
  {
    "Introduction": [
      {
        "key": "intro_1",
        "text": "This part is decrementing agility skill by 2",
        "choices": [
            { "text": "I don't understand choices", "next_key": "intro_2" },
            { "text": "I understand choices", "next_key": "intro_3" }
        ]
      },
      {
        "key": "intro_2",
        "text": "Wrong choice !"
      },
      {
        "key": "intro_3",
        "text": "You made the right choice !"
      }
    ]
  }
]
```

In this example, "intro_1" part is confronting the player with two different choices.

You can also make a choice usable only if the player has an amount as you want on the skill as you want, it's called [special choices](#add-special-choice).


### Add-special-choice

You add special choice that the player can make only if he has an amount as you want on the skill as you want.

Works the same as [choices key](#add-choices), but object take two more strings

Special choice works as choice works, but it must contain two more keys
* A string named "needed_skill" that define the skill that is needed to make this choice.
* An int named "needed_value" that define the amount of needed_skill's skill that is needed to make this choice.

Each special choice object take four strings
* A string named "text" that is the text of a choice.
* A string named "needed_skill" that is the skill that player need.
* An int named "needed_value" that is the amount that the player need.
* A string named "next_key" that is the following part of a choice.


```
"story": [
  {
    "Introduction": [
      {
        "key": "intro_1",
        "text": "This part is decrementing agility skill by 2",
        "choices": [
            { "text": "Run", "next_key": "intro_2" },
            { "text": "Fight", "needed_skill": "agility", "needed_value": 7, "next_key": "intro_3" }
        ]
      },
      {
        "key": "intro_2",
        "text": "You runaway from ennemies"
      },
      {
        "key": "intro_3",
        "text": "You choosed to fight the ennemies !"
      }
    ]
  }
]
```


In this example, "intro_1" part is confronting the player with two different choices including one special choice that the player can make only if he has greater than or equal to 7 in agility.


### Add-test

You can challenge the player with a QTE using "test".

The object take four datas
* A string named "type" that is the type of test. *for the moment there is only one type which is agility*
* An int named "difficulty" that is the difficulty of the test.
* A string named "win_next_key" that is the following part of a choice in case of the player won.
* A string named "lose_next_key" that is the following part of a choice in case of the player lost.

Note that you can't combine choices with [next_key](#add-next-key) or [choices](#add-choices).


```
"story": [
  {
    "Introduction": [
      {
        "key": "intro_1",
        "text": "An agility test is coming !",
        "test": {
          "type": "agility",
          "difficulty": 3,
          "win_next_key": "intro_2",
          "lose_next_key": "intro_3"
        }
      },
      {
        "key": "intro_2",
        "text": "You succeeded on the agility test"
      },
      {
        "key": "intro_3",
        "text": "You have failted on the agility test"
      }
    ] 
  }
]
```

---

*Last updated : 12 January 2021*
