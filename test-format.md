I'm going to run tests like so:

  * For non-GUI operations e.g. accessing the database, I'll make a new database
    file, make changes, try to return them etc. and assert them against expected
    output.
  * For GUI operations, I'll start everything and such normally, but automate
    things (not everything so that I can screenshot etc.)

Or something, since I'll probably use Google Test.
