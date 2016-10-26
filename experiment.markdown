### 1. Failed
**参数：**
```python
experiment_parameters = {
        "max_episodes" : 2000,
        "max_steps" : 10000,
        "memory_size" : 100000,
        "learn_start" : 5000,
        "update_freq": 4,
        "save_freq": 100,
        "save_base": "./output/model",
        "discount": 0.99,
        "ep_start" : 1.,
        "ep_end" : 0.1,
        "ep_endt" : 50000,
        "lr" : 0.00025,
        "tau": 0.001,
        "hist_len" : 4,
        "batch_size" : 32,
        "hidden_units_1": 300,
        "hidden_units_2": 500,
        "state_dim": 24, # Check this
        "vision": False,
        "is_train": True
    }
penalty = -10
reward = penalty * np.abs(obs["trackPos"]) - 0.5 * np.abs(obs["speedX"] * np.sin(obs["angle"]))
```
**现象：**

在`learn_start`之前，一切都看似正常的进行着，anget随机的采取动作来探索动作空间。此时的`ep_max_q`也是正数。
但是，在`learn_start`之后，`max_q`x一下就变成了0，这说明，q函数更新了之后，凡是之前有探索到的动作空间，其q值已经全部都变成了负数，是什么原因还
不太清楚，但是可以在开始学习之后，打印出q值来看一看。

结果图为：`/output/global_info/0q.png` 和 `/output/global_info/0returns.png`

**可能的改变：**

- 由于状态中已经包含了速度，尝试去掉`hist_len`试一试 (YES)
- 从一开始就学习，即`learn_start = 0` (NO)
- reward是否需要改变？ (NO)
- 每一个 step 都进行train，即`update_freq = 1` (YES)


**小结：**
- 之所以`max_q`全部变成了0，是由于最后一层的激活函数设置错了（用了relu），最后改成了 *linear* 之后，q值为0的问题就不存在了

-----

### 2. Failed
**参数：**
```python
experiment_parameters = {
        "max_episodes" : 2000,
        "max_steps" : 10000,
        "memory_size" : 100000,
        "learn_start" : 5000,
        "update_freq": 4,
        "save_freq": 500,
        "save_base": "./output/model",
        "discount": 0.99,
        "ep_start" : 1.,
        "ep_end" : 0.1,
        "ep_endt" : 50000,
        "lr" : 0.00025,
        "tau": 0.001,
        # "hist_len" : 4,
        "batch_size" : 32,
        "hidden_units_1": 300,
        "hidden_units_2": 500,
        "state_dim": 24, # Check this
        "vision": False,
        "is_train": True
    }
penalty = -10
reward = penalty * np.abs(obs["trackPos"]) - 0.5 * np.abs(obs["speedX"] * np.sin(obs["angle"]))
```
**现象：**

在运行到500个episodes之后，`loss`就反而升高了，算法有发散的趋势，在1500个episodes之后，有的q值已经小的离谱（-1500）.
结果图为：`/output/global_info/1_q.png` 和 `/output/global_info/1_r.png`, `output/global_info/1_l.png`


**可能的改变：**

- 把reward重新设置 (YES)
- 减少神经元的数量 (YES)
- 减小学习率 (NO)
- 是不是把问题过于复杂化了，因此简化问题 (YES)


### 2. Not good
**参数：**
```python
experiment_parameters = {
        "max_episodes" : 2000,
        "max_steps" : 10000,
        "memory_size" : 50000,
        "learn_start" : 1,
        "update_freq": 1,
        "save_freq": 200,
        "save_base": "./output/model",
        "discount": 0.99,
        "ep_start" : 1.,
        "ep_end" : 0.1,
        "ep_endt" : 5000,
        "lr" : 0.00025,
        "tau": 0.001,
        "batch_size" : 32,
        "hidden_units_1": 10,
        "state_dim": 3, # Check this
        "vision": False,
        "is_train": True
    }
reward = speed * np.cos(obs["angle"]) - 1.7 * speed * np.sin(np.abs(obs["angle"])) - speed * np.abs(obs["trackPos"]) 
agent.steers = [-1.0, -0.5, -0.2, 0.0, 0.2, 0.5, 1.0]
```

**现象：**

这次学习的时候没有探索阶段，一上来就直接学的，在前1000个episode的时候，`return`基本持平。1000~1800个episode又是下一个阶段，
这一阶段比上一个阶段的`return`要高160左右。而在1800个episode之后，`return`有了大幅度的提升，但是训练结束在第2000个episode处。
有再次接着训练的必要。

**小结：**

这一次的训练结果可以说是前几次中最好的，但是每次学习都有一个很长的平台期，也就是有很长一段时间`return`的数值都不怎么变好。这或许是由于
学习率有点低？TRY higher lr :)


