#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <libwebsockets.h>
#include <string.h>
#include <concord/discord.h>

char * token = NULL;

void on_ready(struct discord *client, const struct discord_ready *event) {
    struct discord_create_guild_application_command params = {
        .name = "ping",
        .description = "Ping the bot. Useful for checking if it's working!"
    };
    discord_create_guild_application_command(client, event->application->id, 1142451678679924818, &params, NULL);
}
 
void on_interaction(struct discord *client, const struct discord_interaction *event) {
    if (event->type != DISCORD_INTERACTION_APPLICATION_COMMAND)
        return; /* return if interaction isn't a slash command */
 
    if (strcmp(event->data->name, "ping") == 0) {
          struct discord_interaction_response params = {
                .type = DISCORD_INTERACTION_CHANNEL_MESSAGE_WITH_SOURCE,
                .data = &(struct discord_interaction_callback_data) {
                      .content = "Pinged! "
                }
          };
          discord_create_interaction_response(client, event->id, event->token, &params, NULL);
    }
}

int main(int argc, char * argv[])
{
    int opt;
    while ((opt = getopt(argc, argv, "t:")) != -1)
    {
        switch (opt)
        {
            case 't':
                token = optarg;
                break;
            default:
                fprintf(stderr, "Usage: %s -t <TOKEN_STRING>\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if(token == NULL)
    {
        fprintf(stderr, "You must provide a token using -t\n");
        exit(EXIT_FAILURE);
    }
    
    struct discord *client = discord_init(token);
    discord_set_on_ready(client, &on_ready);
    discord_set_on_interaction_create(client, &on_interaction);
    discord_run(client);
}