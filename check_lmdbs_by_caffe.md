检查caffe数据集-LMDB格式
=====
```python
import caffe
import lmdb
import numpy as np

env = lmdb.open('path/to/lmdb', readonly=True)

# randomly pick an item, here the first one.
with env.begin() as txn:
  raw = tnx.get('00000000')
datum = caffe.proto.caffe_pb2.Datum()
datum.ParseFromString(raw)

images = np.fromstring(datum.data, dtype=np.uint8)
labels = datum.label
float_data = datum.float_data
```
