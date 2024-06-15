package com.example.rps

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.ImageButton
import android.widget.ImageView
import android.widget.TextView
import com.example.rps.R.drawable.blackhole
import com.example.rps.R.drawable.cloud
import com.example.rps.R.drawable.mountain
import com.example.rps.R.drawable.paper
import com.example.rps.R.drawable.planet
import com.example.rps.R.drawable.rock
import com.example.rps.R.drawable.rocket
import com.example.rps.R.drawable.scissors
import com.example.rps.R.drawable.wind
import kotlin.random.Random

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
    }

    //value to be updated when the computer wins a round.
    private var compScore = 0
    //value to be updated when the player wins a round.
    private var playerScore = 0
    //Theme placeholders
    private var theme = "original"

    fun originalTheme(view: View){
        theme = "original"
        val rockButton = findViewById<ImageButton>(R.id.rockChoice)
        val paperButton = findViewById<ImageButton>(R.id.paperChoice)
        val scissorButton = findViewById<ImageButton>(R.id.scissorsChoice)
        val gameText = findViewById<TextView>(R.id.titleText)
        rockButton.setImageResource(rock)
        paperButton.setImageResource(paper)
        scissorButton.setImageResource(scissors)
        "Rock Paper Scissors Shoot!".also { gameText.text = it }
    }
    fun spaceTheme(view: View){
        theme = "space"
        val rockButton = findViewById<ImageButton>(R.id.rockChoice)
        val paperButton = findViewById<ImageButton>(R.id.paperChoice)
        val scissorButton = findViewById<ImageButton>(R.id.scissorsChoice)
        val gameText = findViewById<TextView>(R.id.titleText)
        rockButton.setImageResource(rocket)
        paperButton.setImageResource(planet)
        scissorButton.setImageResource(blackhole)
        "Rocket Planet Black Hole!".also { gameText.text = it }
    }
    fun natureTheme(view: View){
        theme = "nature"
        val rockButton = findViewById<ImageButton>(R.id.rockChoice)
        val paperButton = findViewById<ImageButton>(R.id.paperChoice)
        val scissorButton = findViewById<ImageButton>(R.id.scissorsChoice)
        val gameText = findViewById<TextView>(R.id.titleText)
        rockButton.setImageResource(mountain)
        paperButton.setImageResource(cloud)
        scissorButton.setImageResource(wind)
        "Mountain Clouds Wind!".also { gameText.text = it }
    }

    //function for when the rock button at the bottom of the screen is selected.
    //view: View is used for the ability to link with the buttons inside of the .xml file.
    fun rockSelected(view: View){
        //This creates a value for the players choice and links it via R.id to the Image View for display on the screen.
        val playerChoice = findViewById<ImageView>(R.id.playerChoice)
        //This creates a value for the computers choice and links it via R.id to the Image View for display on the screen.
        val compChoice = findViewById<ImageView>(R.id.compChoice)
        //This creates a value for display of the winner inside of the text view. It updates inside the function after comparison.
        val winner = findViewById<TextView>(R.id.winnerDisplay)
        //This creates a value for display of the score inside of the text view. IT updates inside the function after comparison.
        val scoreDisplay = findViewById<TextView>(R.id.scoreDisplay)
        //This updates the image resource to the rock icon.
        when(theme) {
            "original" -> {
                playerChoice.setImageResource(rock)
            }
            "space" -> {
                playerChoice.setImageResource(rocket)
            }
            "nature" -> {
                playerChoice.setImageResource(mountain)
            }
        }

        //This takes a random number from 0-2 and add one to it. Then we have a when statement that is like an if else but more efficient.
        //Random is imported above for use here.
        when(Random.nextInt(1,4)) {
            //Above the random number is generated. It is until 4 which means it does not include that number. It will generate a number
            //from 1-3.
            1 -> {
                //When 1 is generated it updates the compChoice ImageView to rock. It is a tie so no score is updated therefore no update
                //to the scoreDisplay is needed.
                when(theme) {
                    "original" -> {
                        compChoice.setImageResource(rock)
                    }
                    "space" -> {
                        compChoice.setImageResource(rocket)
                    }
                    "nature" -> {
                        compChoice.setImageResource(mountain)
                    }
                }
                "It's a tie!".also { winner.text = it }
            }
            2 -> {
                //When 2 is selected here it updates the ImageView to paper for the computer, updates the TextView to you lost, increases
                //the variable at the start of main to one more, then updates the TextView to the new scores.
                when(theme) {
                    "original" -> {
                        compChoice.setImageResource(paper)
                    }
                    "space" -> {
                        compChoice.setImageResource(planet)
                    }
                    "nature" -> {
                        compChoice.setImageResource(cloud)
                    }
                }
                "You lost.".also { winner.text = it }
                compScore += 1
                "Comp: $compScore - Player: $playerScore".also { scoreDisplay.text = it }
            }
            3 -> {
                //When 3 is selected here it updates the ImageView to paper for the computer, updates the TextView to you lost, increases
                //the variable at the start of main to one more, then updates the TextView to the new scores.
                when(theme) {
                    "original" -> {
                        compChoice.setImageResource(scissors)
                    }
                    "space" -> {
                        compChoice.setImageResource(blackhole)
                    }
                    "nature" -> {
                        compChoice.setImageResource(wind)
                    }
                }
                "You won!".also { winner.text = it }
                playerScore += 1
                "Comp: $compScore - Player: $playerScore".also { scoreDisplay.text = it }
            }
        }
    }

    fun paperSelected(view: View){
        val playerChoice = findViewById<ImageView>(R.id.playerChoice)
        val compChoice = findViewById<ImageView>(R.id.compChoice)
        val winner = findViewById<TextView>(R.id.winnerDisplay)
        val scoreDisplay = findViewById<TextView>(R.id.scoreDisplay)
        when(theme) {
            "original" -> {
                playerChoice.setImageResource(paper)
            }
            "space" -> {
                playerChoice.setImageResource(planet)
            }
            "nature" -> {
                playerChoice.setImageResource(cloud)
            }
        }

        when(Random.nextInt(4)) {
            1 -> {
                when(theme) {
                    "original" -> {
                        compChoice.setImageResource(rock)
                    }
                    "space" -> {
                        compChoice.setImageResource(rocket)
                    }
                    "nature" -> {
                        compChoice.setImageResource(mountain)
                    }
                }
                "You won!".also { winner.text = it }
                playerScore += 1
                "Comp: $compScore - Player: $playerScore".also { scoreDisplay.text = it }
            }
            2 -> {
                when(theme) {
                    "original" -> {
                        compChoice.setImageResource(paper)
                    }
                    "space" -> {
                        compChoice.setImageResource(planet)
                    }
                    "nature" -> {
                        compChoice.setImageResource(cloud)
                    }
                }
                "It's a tie!".also { winner.text = it }
            }
            3 -> {
                when(theme) {
                    "original" -> {
                        compChoice.setImageResource(scissors)
                    }
                    "space" -> {
                        compChoice.setImageResource(blackhole)
                    }
                    "nature" -> {
                        compChoice.setImageResource(wind)
                    }
                }
                "You lost.".also { winner.text = it }
                compScore += 1
                "Comp: $compScore - Player: $playerScore".also { scoreDisplay.text = it }
            }
        }
    }

    fun scissorsSelected(view: View){
        val playerChoice = findViewById<ImageView>(R.id.playerChoice)
        val compChoice = findViewById<ImageView>(R.id.compChoice)
        val winner = findViewById<TextView>(R.id.winnerDisplay)
        val scoreDisplay = findViewById<TextView>(R.id.scoreDisplay)
        when(theme) {
            "original" -> {
                playerChoice.setImageResource(scissors)
            }
            "space" -> {
                playerChoice.setImageResource(blackhole)
            }
            "nature" -> {
                playerChoice.setImageResource(wind)
            }
        }

        when(Random.nextInt(4)) {
            1 -> {
                when(theme) {
                    "original" -> {
                        compChoice.setImageResource(rock)
                    }
                    "space" -> {
                        compChoice.setImageResource(rocket)
                    }
                    "nature" -> {
                        compChoice.setImageResource(mountain)
                    }
                }
                "You lost.".also { winner.text = it }
                compScore += 1
                "Comp: $compScore - Player: $playerScore".also { scoreDisplay.text = it }
            }
            2 -> {
                when(theme) {
                    "original" -> {
                        compChoice.setImageResource(paper)
                    }
                    "space" -> {
                        compChoice.setImageResource(planet)
                    }
                    "nature" -> {
                        compChoice.setImageResource(cloud)
                    }
                }
                "You won!".also { winner.text = it }
                playerScore += 1
                "Comp: $compScore - Player: $playerScore".also { scoreDisplay.text = it }
            }
            3 -> {
                when(theme) {
                    "original" -> {
                        compChoice.setImageResource(scissors)
                    }
                    "space" -> {
                        compChoice.setImageResource(blackhole)
                    }
                    "nature" -> {
                        compChoice.setImageResource(wind)
                    }
                }
                "It's a tie!".also { winner.text = it }
            }
        }
    }

    //A function to reset the variables to 0 for the score keeping. These are declared above all the functions while inside of main.
    fun resetScores(view: View){
        //Declaration of the scoreDisplay for updating the TextView. This must be done inside of the function or it will break the app.
        val scoreDisplay = findViewById<TextView>(R.id.scoreDisplay)
        //variables reset to 0
        compScore = 0
        playerScore = 0
        //The updating of the textView after pressing the button. Minor errors due to the variables inside of here always being 0.
        //This is how we want it to work though.
        "Comp: $compScore - Player: $playerScore".also { scoreDisplay.text = it }
    }

}
