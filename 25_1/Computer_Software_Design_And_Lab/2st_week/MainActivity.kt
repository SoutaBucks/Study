package com.example.myapplication_2

import android.os.Bundle
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat

/*

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContentView(R.layout.activity_main)
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main)) { v, insets ->
            val systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars())
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom)
            insets
        }
    }
}
*/

open class Person(school: String) {
    var school = school
    open fun print_school() {
        println(school)
    }
}
/*
enum class Delivery {STANDARD, EXPEDITED}
class Order (val itemCount: Int)

fun getShippingCostCaculator (
    delivery: Delivery
) : (Order) -> Double {
    if(delivery == Delivery.EXPEDITED)
        return {order -> 6 + 2.1 * order.itemCount}
    return {order -> 61.2 * order.itemCount}
}*/


/*//예제 1
fun main() {
    val a = readLine()
    println("입력 받을 숫자: ${a!!}")

    for(i in 1..a.toInt()) {
        if(i % 2 != 0) {
            print("${i}    ")
        }
    }
}*/


/*//예제 2
enum class Food { pizza, burger, chicken }

class Lunch(var menu: Food, var price: Int) {
    fun choice_lunch() {
        println("menu : ${menu}, price : ${price}")
    }
}

fun main() {
    var lunch : MutableList<Lunch> = mutableListOf()
    lunch.add(Lunch(Food.pizza, 15000))
    lunch.add(Lunch(Food.burger, 7000))
    lunch.add(Lunch(Food.chicken, 25000))

    var myLunch = lunch.filter { it.price < 10000 }
    for(lunch in myLunch)
        lunch.choice_lunch()
}*/


//예제 3
fun main() {
    while (true) {
        var a : String ? = readLine()
        if(a?.filter { it in 'A'..'Z' || it in 'a'..'z' }?.length == a?.length)
            println(a?.uppercase())
        else {
            println("error with = ${a}")
            break
        }
    }
}