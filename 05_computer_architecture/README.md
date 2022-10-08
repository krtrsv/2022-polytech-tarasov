1. Какой процесс имеет наименьший идентификатор?

```bash
$ ps -Ao pid,comm --sort=pid | head -n 2
  PID COMMAND
    1 systemd
```

2. Какой идетификтор у вашего текущего shell-процесса?

```bash
$ ps -p $$
    PID TTY          TIME CMD
   5930 pts/0    00:00:18 zsh
```

3. Сколько всего запущено процессов?

```bash
$ ps -A | wc -l
257
```
