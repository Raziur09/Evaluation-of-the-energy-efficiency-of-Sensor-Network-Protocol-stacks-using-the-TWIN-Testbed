import pandas as pd
import matplotlib.pyplot as plt
import numpy as np



df = pd.read_csv('ContikiMACout.csv',index_col='TimeStamp', names=['TimeStamp','ID','Energest','CPU','LPM','Transmit','Listen'])

# df = df.sort_values('ID', ascending=True)

df['Total'] = (df.CPU / 32768) * 0.08 + (df.LPM / 32768) * 0.07 + (df.Transmit / 32768) * 0.05 + (df.Listen / 32768) * 0.3


df1 = df[df['ID'] == 1]
# df2 = df[df['ID'] == 2]
# df3 = df[df['ID'] == 3]
# df4 = df[df['ID'] == 4]
# df5 = df[df['ID'] == 5]
# df6 = df[df['ID'] == 6]
# df7 = df[df['ID'] == 7]
# df8 = df[df['ID'] == 8]
# df9 = df[df['ID'] == 9]
# df10 = df[df['ID'] == 10]
# df11 = df[df['ID'] == 11]
# df12 = df[df['ID'] == 12]


plt.plot(df1.Energest, df1.Total)
# plt.plot(df2.Energest, df2.Total)
# plt.plot(df3.Energest, df3.Total)
# plt.plot(df4.Energest, df4.Total)
# plt.plot(df5.Energest, df5.Total)
# plt.plot(df6.Energest, df6.Total)
# plt.plot(df7.Energest, df7.Total)
# plt.plot(df8.Energest, df8.Total)
# plt.plot(df9.Energest, df9.Total)
# plt.plot(df10.Energest, df10.Total)
# plt.plot(df11.Energest, df11.Total)
# plt.plot(df12.Energest, df12.Total)

plt.xlabel('Energest')
plt.ylabel('Total Current')
plt.title('Graph')
plt.show()

df = df.to_csv('FinalCurrent.csv')




