# clients/news_client.py
from clients.abstract_client import AbstractDataClient

class NewsClient(AbstractDataClient):
    POSITIVE_WORDS = [
        "gain", "growth", "rise", "profit", "positive", "up",
        "surge", "bullish", "record", "strong"
    ]

    NEGATIVE_WORDS = [
        "loss", "drop", "decline", "fall", "negative", "down",
        "crash", "bearish", "weak", "risk"
    ]

    def __init__(self, api_key: str):
        super().__init__(
            api_key=api_key,
            base_url="https://newsapi.org/v2/everything"
        )

    def fetch_data(self, query: str):
        params = {
            "q": query,
            "language": "en",
            "sortBy": "publishedAt",
            "apiKey": self.api_key
        }
        return self.get(params)

    def transform_data(self, raw_data):
        articles = raw_data.get("articles", [])
        results = []

        for article in articles[:5]:  # top 5 articles
            title = article.get("title", "")
            description = article.get("description", "")
            content = f"{title} {description}".lower()

            sentiment = self.analyze_sentiment(content)

            results.append({
                "title": title,
                "source": article.get("source", {}).get("name"),
                "sentiment": sentiment
            })

        return results

    def analyze_sentiment(self, text: str):
        positive_score = sum(word in text for word in self.POSITIVE_WORDS)
        negative_score = sum(word in text for word in self.NEGATIVE_WORDS)

        if positive_score > negative_score:
            return "Positive"
        elif negative_score > positive_score:
            return "Negative"
        return "Neutral"
