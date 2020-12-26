# interpolator
Newton's Divided-Difference Interpolation (Visualized to Bitmap Image)

## Running Program Example
```
[michael@arch-vivobook build] $ ./interpolator
Enter input file: input.txt
Enter X scale (1 for default): 5
Enter Y scale (1 for default): 0.04
Enter polynomial degree (>0): 5
Show interpolated values? (y/n) n
Enter output file (bitmap): output.bmp
Enter image width (1024 for default): 800
Enter image height (1024 for default): 800
Generating bitmap...
Done
Enter input file: ^C
```

### Contents of input.txt:
```
0	3856
1	4018
2	4090
3	3882
4	3896
5	4011
6	4056
7	4312
8	4435
9	4595
10	4757
11	4981
12	4891
13	5001
14	5193
15	5346
16	5501
17	5794
18	5817
19	6089
20	6038
21	6274
22	6459
23	6553
24	6545
25	6676
26	6746
27	6957
28	7051
29	7231
30	7196
31	7356
32	7441
33	7727
34	8101
35	8272
36	8408
37	8546
38	8777
39	8762
40	8818
41	9109
42	9042
43	9022
44	8638
45	8347
46	8178
47	7816
48	7565
49	7395
50	7302
51	7137
52	6800
53	6846
54	6729
55	6632
56	6524
57	6414
58	6202
59	6031
60	5976
```

### Resulting output.bmp:
![Output Example](https://github.com/michaelrk02/interpolator/raw/master/docs/sample-output.jpg)
