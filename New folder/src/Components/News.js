import React, { Component } from 'react'
import Newitem from './Newitem'

export class News extends Component {
    constructor() {
        super();
        console.log("hi, I am constructor");

        this.state = {
            articles: [],
            loading: false
        }
    }

    async componentDidMount() {
        let url = "https://newsapi.org/v2/top-headlines?country=us&category=business&apiKey=71edbeab3fd440b4b8120aacd37725e3";
        this.setState({ loading: true });

        let data = await fetch(url);
        let parsedData = await data.json();
        console.log(parsedData);

        this.setState({
            articles: parsedData.articles,
            loading: false
        });
    }

    render() {
        return (
            <div className='container my-3'>
                <h2>DailyScope: Top Headlines</h2>
                <div className='row'>
                    {this.state.articles.map((element) => {
                        return (
                            <div className='col-md-3' key={element.url}>
                                <Newitem
                                    title={element.title ? element.title.slice(0,45) : ""}
                                    description={element.description ? element.description.slice(0,88) : ""}
                                    imgurl={element.urlToImage}
                                    newsurl={element.url}
                                />
                            </div>
                        )
                    })}
                </div>
            </div>
        )
    }
}

export default News
