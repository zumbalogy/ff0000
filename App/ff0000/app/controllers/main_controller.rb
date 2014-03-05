class MainController < ApplicationController

    def index
    end

    def toggle
        # api call to function toggle defined via spark cloud to spark core

        # spark cloud access token
        access_token = ENV['SPARK_TOKEN']

        # spark core device id
        grants = ENV['GRANTS']
        url = "https://api.spark.io/v1/devices/" + grants + "/ledstate"

        # require 'httparty'
        HTTParty.post(url, {
            body: {access_token: access_token, args:"toggle"},
            headers: {'Content-Type' => 'application/x-www-form-urlencoded'}
        })

        render nothing: true
    end


    def status
        access_token = ENV['SPARK_TOKEN']

        grants = ENV['GRANTS']
        url = "https://api.spark.io/v1/devices/" + grants + "/ledstate"

        response = HTTParty.post(url, {
            body: {access_token: access_token, args:"status"},
            headers: {'Content-Type' => 'application/x-www-form-urlencoded'}
        })

        status = response['return_value']


        render json: {status: status}
    end

end









