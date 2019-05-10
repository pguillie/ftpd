/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replies.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 16:58:46 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/10 17:26:56 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLIES_H
# define REPLIES_H

# define REP_CMD_OK	"200 Command okay."
# define REP_READY	"220 Service ready."
# define REP_SHUT_DOWN	"421 Service not available, closing control connection."
# define REP_SYNTAX_ERR	"500 Syntax error, command unrecognized."
# define REP_CMD_TOO_LONG "500 Command too long."

#endif /* REPLIES_H */
