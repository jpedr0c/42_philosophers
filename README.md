<p align="center">
<a href="https://github.com/jpedr0c/42_philosophers">
<img src="./philosophers.png" height="120" width="120">
</a>
</p>
<h1 align=center>
  <strong> PHILOSOPHERS </strong>
</h1>

<p align="center">
  <sub> Philosophers teaches about concepts such as concurrency, synchronization and deadlock by implementing a philosophers dinner simulator.
  <sub>
</p>


[![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)](#table-of-contents)

<p align="center">
  <a href="#About"> 💡 About the project </a>&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;
  <a href="#Explanation"> 📝 Explanation</a>&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;
  <a href="#HowUse"> ⚙️ How to use</a>&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;
  <a href="#Credits"> 🏆 Credits</a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
</p>

<br/>

<a id="About"></a>
## 💡 About the project
> The project involves the simulation of a dinner table with philosophers, where each philosopher is sitting in a chair and there is a bifurcation to the left and right of each chair. Philosophers spend their time thinking, eating and sleeping but they can only eat if they have two forks, one on each side.
The program simulating this dinner must ensure that the philosophers are not stuck in a deadlock, where no philosopher can pick up a fork that is already being used by another philosopher.

<br/>

<a id="Explanation"></a>
## 📝 Explanation
- One or more philosophers sit at a round table.
- The philosophers alternatively eat, think, or sleep
  - While they are eating, they are not thinking nor sleeping.
  - While thinking, they are not eating nor sleeping.
  - While sleeping, they are not eating nor thinking.
- There are also forks on the table. There are as many forks as philosophers.
- A philosopher takes their right and their left forks to eat, one in each hand.
- When a philosopher has finished eating, they put their forks back on the table and start sleeping. Once awake, they start thinking again. The simulation stops when a philosopher dies of starvation.
- Every philosopher needs to eat and should never starve.
- Philosophers don’t speak with each other.
- Philosophers don’t know if another philosopher is about to die
- The program should take the following arguments:
  - `nb_of_philosophers`: the number of philosophers and also the number of forks.
  - `time_to_die(ms)`: if a philosophers didn't start eating `time_to_die` since the beginning of their last meal or the beginning of the simulation, they die.
  - `time_to_eat(ms)`: the time it takes for a philosophers to eat. During that time, they will need to hold two forks.
  - `time_to_sleep(ms)`: the time a philosophers will spend sleeping.
  - `nb_times_philosopher_must_eat(OPTIONAL)`: if all philosophers have eaten at least `nb_times_philosopher_must_eat` times, the simulation stops. If not specified, the simulation stops when a philosophers dies.
```sh
./philo [nb_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] *[nb_times_philosopher_must_eat]*
```

<br/>

<a id="HowUse"></a>
## ⚙️ How to use

1. Clone this repository
```sh
git clone https://github.com/jpedr0c/42_philosophers.git
```
2. In the project directory, compile the program using the following command
```sh
make
```
3. To use the program, run the following command
```sh
./philo 5 800 200 200 7
```
- Simulation stops when eat 7 times
<details>
<summary>📖 Examples to use</summary>

## 📖 Examples to use
- Nobody dies:
```sh
./philo 5 800 200 200
```
```sh
./philo 2 800 200 200
```
```sh
./philo 4 410 200 200
```
```sh
./philo 4 2147483647 200 200
```

- One philosopher die:
```sh
./philo 4 310 200 200
```
```sh
./philo 4 500 200 2147483647
```
```sh
./philo 4 200 210 200
```

- Return error:
```sh
./philo 1 800 200 200
```
```sh
./philo 4 500 200 1.2
```
```sh
./philo 4 0 200 200
```
```sh
./philo 4 -500 200 200
```
```sh
./philo 4 214748364732 200 200
```
<br/>
</details>

4. If you want to remove the object files generated during compilation
```sh
make clean
```
5. If you want to remove the object files and executable generated during compilation
```sh
make fclean
```

<br/>

<a id="Credits"></a>
## 🏆 Credits
| [<img src="https://avatars.githubusercontent.com/u/78514252?v=4" width="300" style="border-radius:50%"><br><sub> João Pedro </sub>](https://www.linkedin.com/in/jpedroc) | <p align="justify">***Thank you for taking the time to review my project. If you have any questions or would like to connect with me, please feel free to reach out to me on [LinkedIn](https://www.linkedin.com/in/jpedroc)***</p> | 
|---|---|
