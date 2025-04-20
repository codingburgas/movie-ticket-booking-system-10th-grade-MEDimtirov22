#include "data.h"

City cities[] = {
    {"New York", {
        {"AMC Empire 25"},
        {"Regal E-Walk"},
        {"Cinema Village"},
        {"Angelika Film Center"}
    }},
    {"Los Angeles", {
        {"TCL Chinese Theatre"},
        {"AMC Sunset 5"},
        {"Arclight Hollywood"},
        {"The Landmark"}
    }},
    {"Chicago", {
        {"AMC River East 21"},
        {"Landmark's Century Centre"},
        {"Music Box Theatre"},
        {"ShowPlace ICON"}
    }},
    {"San Francisco", {
        {"Alamo Drafthouse"},
        {"AMC Metreon 16"},
        {"Roxie Theater"},
        {"Castro Theatre"}
    }},
    {"Houston", {
        {"Cinemark Memorial City"},
        {"Regal Edwards Greenway Grand"},
        {"AMC Gulf Pointe 30"},
        {"Studio Movie Grill"}
    }}
};


Movie movies[] = {
    // Action
    {"The Batman", "Action"},
    {"Spider-Man: No Way Home", "Action"},
    {"Inception", "Action"},
    {"John Wick", "Action"},
    {"Mad Max: Fury Road", "Action"},
    {"Die Hard", "Action"},

    // Adventure
    {"Avatar 2", "Adventure"},
    {"The Martian", "Adventure"},
    {"Indiana Jones", "Adventure"},
    {"Jumanji", "Adventure"},
    {"Pirates of the Caribbean", "Adventure"},
    {"Jurassic Park", "Adventure"},

    // Romance
    {"The Notebook", "Romance"},
    {"Titanic", "Romance"},
    {"Pride and Prejudice", "Romance"},
    {"La La Land", "Romance"},
    {"A Walk to Remember", "Romance"},
    {"Me Before You", "Romance"},

    // Animation
    {"Inside Out", "Animation"},
    {"Moana", "Animation"},
    {"Toy Story", "Animation"},
    {"Frozen", "Animation"},
    {"Shrek", "Animation"},
    {"Coco", "Animation"},

    // Horror
    {"Get Out", "Horror"},
    {"A Quiet Place", "Horror"},
    {"The Conjuring", "Horror"},
    {"It", "Horror"},
    {"Hereditary", "Horror"},
    {"Insidious", "Horror"}
};


string genres[] = { "Action", "Adventure", "Romance", "Animation", "Horror" };
