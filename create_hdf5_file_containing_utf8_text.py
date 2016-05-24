import h5py

f = h5py.File("true_victory.hdf5", 'w', libver='earliest')
dt = h5py.special_dtype(vlen=str)
content = str("正勝吾勝　勝速日")
dset = f.create_dataset("message",(len(content),),dt)
dset[...] = content
f.flush()
f.close()

