# main.py
from aggregator import FinancialAggregator
from dotenv import load_dotenv
import os

load_dotenv()
STOCK_API_KEY = os.getenv("ALPHA_VANTAGE_API_KEY")
NEWS_API_KEY = os.getenv("NEWS_API_KEY")

if not STOCK_API_KEY or not NEWS_API_KEY:
    raise ValueError("Please set your API keys in the .env file!")

aggregator = FinancialAggregator(STOCK_API_KEY, NEWS_API_KEY)

symbol = input("Enter company stock symbol (e.g., AAPL, TSLA): ").upper()
news_query = input("Enter news keyword (optional, press Enter to skip): ").strip()
news_query = news_query if news_query else None

try:
    insights = aggregator.get_company_insights(symbol, news_query)
except Exception as e:
    print("Error fetching data:", e)
    exit(1)


print("\n==============================")
print(f"Financial Insights for {symbol}")
print("==============================\n")

# Stock info
stock = insights.get("stock_data")
if "error" in stock:
    print(stock["error"])
else:
    print(f"Latest Close Price: ${stock['latest_close']}")
    change = stock['price_change']
    sign = "▲" if change > 0 else "▼" if change < 0 else "→"
    print(f"Price Change: {sign} {abs(change)} (${stock['percent_change']}%)\n")

news = insights.get("news", [])
if not news:
    print("No news found for this company.")
else:
    print("Top News Articles & Sentiment:")
    for idx, article in enumerate(news, 1):
        title = article["title"]
        source = article["source"]
        sentiment = article["sentiment"]
        print(f"{idx}. [{sentiment}] {title} ({source})")
