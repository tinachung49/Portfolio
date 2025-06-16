#需事先安裝的套件：
#!pip install yfinance -q
#!pip install requests

import yfinance as yf

#股價
df = yf.Ticker("MSFT").history(period="max")
df

#版本一：計算前一年度的 Research and Development Ratio
import yfinance as yf

tickers = ['MSFT']

for ticker in tickers:
    stock = yf.Ticker(ticker)
    financials = stock.financials

    print(f"\n{ticker} available financial rows:")
    print(financials.index)

    try:
        r_and_d = financials.loc['Research And Development'][0]
        revenue = financials.loc['Total Revenue'][0]
        r_d_ratio = r_and_d / revenue
        print(f'{ticker}: R&D Ratio = {r_d_ratio:.2%}')
    except KeyError as e:
        print(f"{ticker}: 缺少欄位 {e}")

#版本二：查多個公司且多個年度的R&D Ratio
import yfinance as yf

tickers = ['MSFT','GOOG'] # 這裡改公司

for ticker in tickers:
    stock = yf.Ticker(ticker)
    financials = stock.financials  # 這是年度財報

    print(f"\n{ticker} available financial rows:")
    print(financials.index)

    try:
        r_and_d_series = financials.loc['Research And Development']
        revenue_series = financials.loc['Total Revenue']

        print(f"\n{ticker}: R&D to Revenue Ratio by Year")
        for date in r_and_d_series.index:
            year = date.year
            if 2023 <= year <= 2024: # 這裡改年度
                r_and_d = r_and_d_series[date]
                revenue = revenue_series[date]
                r_d_ratio = r_and_d / revenue if revenue else 0
                print(f'{year}: R&D Ratio = {r_d_ratio:.2%}')
    except KeyError as e:
        print(f"{ticker}: 缺少欄位 {e}")

#版本三：手動輸入公司
import yfinance as yf
import pandas as pd

tickers = ['MSFT'] #改公司
year_range = range(2020,2025) #改年度

result_df = pd.DataFrame(index=year_range)

for ticker in tickers:
    stock = yf.Ticker(ticker)
    financials = stock.financials

    try:
        r_and_d_series = financials.loc['Research And Development']
        revenue_series = financials.loc['Total Revenue']

        ratios = {}
        for date in r_and_d_series.index:
            year = date.year
            if year in year_range:
                r_and_d = r_and_d_series[date]
                revenue = revenue_series[date]
                r_d_ratio = r_and_d / revenue if revenue else None
                ratios[year] = r_d_ratio

        company_ratios = pd.Series(ratios, name=ticker)
        result_df[ticker] = company_ratios

    except KeyError as e:
        print(f"{ticker}: 缺少欄位 {e}")
        continue

result_df = result_df.transpose()
result_df.to_excel('r_d_ratios.xlsx')

# 自動下載計算結果的excel檔
from google.colab import files
files.download('r_d_ratios.xlsx')

#版本四：可以直接讀取有大量Tickers的excel檔，並將計算好的 R&D ratio匯出成excel檔
import yfinance as yf
import pandas as pd
from google.colab import files
uploaded = files.upload()

# 讀取 Excel 中的 ticker 名單
ticker_df = pd.read_excel('XBI成分股.xlsx')  # 確保這個檔案已上傳到 Colab
tickers = ticker_df['Ticker'].dropna().unique().tolist()  # 轉成 list

year_range = range(2020, 2025)
result_df = pd.DataFrame(index=year_range)

for ticker in tickers:
    stock = yf.Ticker(ticker)
    financials = stock.financials

    try:
        r_and_d_series = financials.loc['Research And Development']
        revenue_series = financials.loc['Total Revenue']

        ratios = {}
        for date in r_and_d_series.index:
            year = date.year
            if year in year_range:
                r_and_d = r_and_d_series[date]
                revenue = revenue_series[date]
                r_d_ratio = r_and_d / revenue if revenue else None
                ratios[year] = r_d_ratio

        company_ratios = pd.Series(ratios, name=ticker)
        result_df[ticker] = company_ratios

    except KeyError as e:
        print(f"{ticker}: 缺少欄位 {e}")
        continue

result_df = result_df.transpose()
result_df.to_excel('r_d_ratios.xlsx')

# 自動下載
from google.colab import files
files.download('r_d_ratios.xlsx')