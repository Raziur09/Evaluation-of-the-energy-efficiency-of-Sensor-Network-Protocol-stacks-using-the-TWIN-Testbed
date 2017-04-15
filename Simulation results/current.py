import pandas as pd
import matplotlib.pyplot as plt
import numpy as np



df = pd.read_csv('ContikiMac1out.csv', names=['Energest','CPU','LPM','Transmit','Listen','ID'])

#df = df.sort_values('ID', ascending=True)

df['TotalQ'] = (df.CPU / 32768) * 0.008 + (df.LPM / 32768) * 2e-5 + (df.Transmit / 32768) * 0.00919 + (df.Listen / 32768) * 0.01886
#df['Current'] = df.TotalQ / df.Energest
#df['Power'] = df.Current * 3.6

df1 = df[df['ID'] == 1]
df2 = df[df['ID'] == 2]
#df3 = df[df['ID'] == 3]
#df4 = df[df['ID'] == 4]
# df5 = df[df['ID'] == 5]
# df6 = df[df['ID'] == 6]
# df7 = df[df['ID'] == 7]
# df8 = df[df['ID'] == 8]
# df9 = df[df['ID'] == 9]
# df10 = df[df['ID'] == 10]
# df11 = df[df['ID'] == 11]
# df12 = df[df['ID'] == 12]


plt.plot(df1.Energest, df1.TotalQ)
plt.plot(df2.Energest, df2.TotalQ, 'r-', label='2')
#plt.plot(df3.Energest, df3.TotalQ, 'g-', label='3')
#plt.plot(df4.Energest, df4.TotalQ)
# plt.plot(df5.Energest, df5.TotalQ)
# plt.plot(df6.Energest, df6.TotalQ)
# plt.plot(df7.Energest, df7.TotalQ)
# plt.plot(df8.Energest, df8.TotalQ)
# plt.plot(df9.Energest, df9.TotalQ)
# plt.plot(df10.Energest, df10.TotalQ)
# plt.plot(df11.Energest, df11.TotalQ)
# plt.plot(df12.Energest, df12.TotalQ)

plt.xlabel('Time/Hour')
plt.ylabel('Q/C')
plt.title('Q vs T')



plt.show()

df = df.to_csv('FinalCurrent2.csv')




