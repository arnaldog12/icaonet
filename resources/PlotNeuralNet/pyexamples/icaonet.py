import sys
sys.path.append('../')
from pycore.tikzeng import *

# defined your arch
arch = [
    to_head('..'),
    to_cor(),
    to_begin(),

    #input
    to_input('FRGC_04279d92.jpg'),

    # encoder
    to_ConvRelu(name='conv_1', s_filer=160, n_filer=32, offset="(0,0,0)", to="(0,0,0)", width=3, height=40, depth=40),
    to_Pool(name="pool_1", offset="(0,0,0)", to='(conv_1-east)', width=1, height=20, depth=20, opacity=0.5),

    to_ConvRelu(name='conv_2', s_filer=80, n_filer=64, offset="(2,0,0)", to="(pool_1-east)", width=6, height=20, depth=20),
    to_Pool(name="pool_2", offset="(0,0,0)", to='(conv_2-east)', width=1, height=10, depth=10, opacity=0.5),
    to_connection("pool_1", "conv_2"),

    to_ConvRelu(name='conv_3', s_filer=40, n_filer=128, offset="(1,0,0)", to="(pool_2-east)", width=12, height=10, depth=10),
    to_Pool(name="pool_3", offset="(0,0,0)", to='(conv_3-east)', width=1, height=5, depth=5, opacity=0.5),
    to_connection("pool_2", "conv_3"),

    to_ConvRelu(name='conv_4', s_filer=20, n_filer=256, offset="(1,0,0)", to="(pool_3-east)", width=24, height=5, depth=5),
    to_Pool(name="pool_4", offset="(0,0,0)", to='(conv_4-east)', width=1, height=2, depth=2, opacity=0.5),
    to_connection("pool_3", "conv_4"),

    to_Conv(name='conv_5', s_filer=10, n_filer=256, offset="(1,0,0)", to="(pool_4-east)", width=24, height=2, depth=2, caption="embeddings"),
    to_connection("pool_4", "conv_5"),

    # decoder
    to_ConvRelu(name='4_conv', s_filer=20, n_filer=256, offset="(1,0,0)", to="(conv_5-east)", width=24, height=5, depth=5),
    to_connection("conv_5", "4_conv"),

    to_ConvRelu(name='3_conv', s_filer=40, n_filer=128, offset="(1,0,0)", to="(4_conv-east)", width=12, height=10, depth=10),
    to_connection("4_conv", "3_conv"),

    to_ConvRelu(name='2_conv', s_filer=80, n_filer=64, offset="(1,0,0)", to="(3_conv-east)", width=6, height=20, depth=20),
    to_connection("3_conv", "2_conv"),

    to_ConvRelu(name='1_conv', s_filer=160, n_filer=32, offset="(2,0,0)", to="(2_conv-east)", width=3, height=40, depth=40),
    to_connection("2_conv", "1_conv"),

    to_ConvSoftMax(name="decoded", s_filer=160, offset="(2,0,0)", to="(1_conv-east)", width=1, height=40, depth=40, caption="decoded \\\\ (unsupervised)"),
    to_connection("1_conv", "decoded"),

    # global avg pool
    to_GlobalAvgPool(name="avg_pool", s_filer=256, offset="(3,6,0)", to="(conv_5-east)", width=2, height=2, depth=24, opacity=0.5),
    to_connection2("conv_5", "avg_pool"),

    # requirements
    to_SoftMax(name="dense_1", s_filer=64, offset="(2,0,0)", to="(avg_pool-east)", width=2, height=2, depth=12, opacity=0.5, fill="\DcnvColor"),
    to_connection("avg_pool", "dense_1"),

    to_SoftMax(name="dense_2", s_filer=32, offset="(2,0,0)", to="(dense_1-east)", width=2, height=2, depth=6, opacity=0.5, fill="\DcnvColor"),
    to_connection("dense_1", "dense_2"),

    to_SoftMax(name="outputs", s_filer=23, offset="(2,0,0)", to="(dense_2-east)", width=2, height=2, depth=5, opacity=0.5, caption="multilabel \\\\ (supervised)"),
    to_connection("dense_2", "outputs"),

    # eye landmarks
    to_SoftMax(name="dense_3", s_filer=64, offset="(0,0,-6)", to="(avg_pool-east)", width=2, height=2, depth=12, opacity=0.5, fill="\DcnvColor"),
    to_connection("avg_pool", "dense_3"),

    to_SoftMax(name="dense_4", s_filer=64, offset="(2,0,0)", to="(dense_3-east)", width=2, height=2, depth=12, opacity=0.5, fill="\DcnvColor"),
    to_connection("dense_3", "dense_4"),

    to_SoftMax(name="outputs_eyes", s_filer=4, offset="(2,0,0)", to="(dense_4-east)", width=2, height=2, depth=2, opacity=0.5, caption="landmarks \\\\ (supervised)"),
    to_connection("dense_4", "outputs_eyes"),

    to_end(),
    ]


def main():
    namefile = str(sys.argv[0]).split('.')[0]
    to_generate(arch, namefile + '.tex')

if __name__ == '__main__':
    main()

# bash ..\tikzmake.sh icaonet
# https://github.com/HarisIqbal88/PlotNeuralNet/issues/43