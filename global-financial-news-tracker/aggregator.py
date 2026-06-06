# aggregator.py
from clients.stock_client import StockClient
from clients.news_client import NewsClient

class FinancialAggregator:
    def __init__(self, stock_api_key: str, news_api_key: str):
        self.stock_client = StockClient(stock_api_key)
        self.news_client = NewsClient(news_api_key)

    def get_company_insights(self, symbol: str, news_query: str = None):
        raw_stock = self.stock_client.fetch_data(symbol)
        stock_data = self.stock_client.transform_data(raw_stock)
        if stock_data is None:
            stock_data = {"error": "Stock data not available"}

        # News
        query = news_query if news_query else symbol
        raw_news = self.news_client.fetch_data(query)
        news_data = self.news_client.transform_data(raw_news)

        return {
            "symbol": symbol,
            "stock_data": stock_data,
            "news": news_data
        }

if __name__ == "__main__":
    import os
    from dotenv import load_dotenv

    load_dotenv()
    STOCK_API_KEY = os.getenv("ALPHA_VANTAGE_API_KEY")
    NEWS_API_KEY = os.getenv("NEWS_API_KEY")

    aggregator = FinancialAggregator(STOCK_API_KEY, NEWS_API_KEY)
    insights = aggregator.get_company_insights("AAPL")
    print(insights)
