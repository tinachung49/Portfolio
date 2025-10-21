#There are four versions
#download in advance：
#!pip install yfinance -q
#!pip install requests

import yfinance as yf

#Stock price
df = yf.Ticker("MSFT").history(period="max")
df

#Version 1：count Research and Development Ratio in previous year
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

#Version 2: Look up R&D Ratios for multiple companies and multiple years.
import yfinance as yf

tickers = ['MSFT','GOOG'] 

for ticker in tickers:
    stock = yf.Ticker(ticker)
    financials = stock.financials  

    print(f"\n{ticker} available financial rows:")
    print(financials.index)

    try:
        r_and_d_series = financials.loc['Research And Development']
        revenue_series = financials.loc['Total Revenue']

        print(f"\n{ticker}: R&D to Revenue Ratio by Year")
        for date in r_and_d_series.index:
            year = date.year
            if 2023 <= year <= 2024: 
                r_and_d = r_and_d_series[date]
                revenue = revenue_series[date]
                r_d_ratio = r_and_d / revenue if revenue else 0
                print(f'{year}: R&D Ratio = {r_d_ratio:.2%}')
    except KeyError as e:
        print(f"{ticker}: 缺少欄位 {e}")

#Version 3: Manually input company tickers.
import yfinance as yf
import pandas as pd

tickers = ['MSFT'] 
year_range = range(2020,2025) 

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


from google.colab import files
files.download('r_d_ratios.xlsx')

#Version 4: Directly read an Excel file containing a large list of tickers and export the calculated R&D ratios to an Excel file.
import yfinance as yf
import pandas as pd
from google.colab import files
uploaded = files.upload()

ticker_df = pd.read_excel('XBI成分股.xlsx')  
tickers = ticker_df['Ticker'].dropna().unique().tolist()  

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


from google.colab import files
files.download('r_d_ratios.xlsx')


