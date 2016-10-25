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

- 把reward重新设置
- 减少神经元的数量
- 减小学习率
- 是不是把问题过于复杂化了
